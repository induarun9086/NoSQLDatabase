/*
 * File:   main.cpp
 * Author: chirag
 *
 * Created on April 22, 2015, 11:40 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "main.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/thread/thread.hpp>

using namespace boost::interprocess;

char* mem;

using namespace std;

void notify_thread() {
    int stringLength;
    int currentCount = 0;
    while (1) {

        sleep(1);
        if (currentCount != mem[1]) {
            currentCount = mem[1];


            if (mem[0] == NOSQL_DATABASE_NOTIFY_ADD) {

                cout << "Item has been added" << endl << &mem[2] << endl << ">>";
            }


            if (mem[0] == NOSQL_DATABASE_NOTIFY_UPDATE) {
                cout << "Item has been updated" << endl << &mem[2] << endl << ">>";
            }
        }


    }

}

int main(int argc, char* argv[]) {
    /* Validate the number of arguments */
    if (argc < 2) {
        cout << "Provide argument s for server or c for client" << endl;
    } else {
        /* If option s is given then we should run in server mode */
        if (argv[1][0] == 's') {

            shared_memory_object shm(open_or_create, "MySharedMemory",
                    read_write);

            //Set size
            shm.truncate(1000);

            //Map the whole shared memory in this process
            mapped_region region(shm, read_write);

            //Write all the memory to 0
            memset(region.get_address(), 0, region.get_size());

            mem = static_cast<char*> (region.get_address());
            doServerProcess();
        } else /* Else in client mode */ {
            shared_memory_object shm(open_only, "MySharedMemory", read_write);
            mapped_region region(shm, read_write);
            mem = static_cast<char*> (region.get_address());
            boost::thread workerThread(notify_thread);
            doClientProcess();
        }
    }
    return 0;
}

bool parseCommand(string command, struct ipcMsg* psendMsg) {
    bool error = true;
    string commandString;
    stringstream commandstream(command);
    commandstream >> commandString;
    if (commandString.compare("open") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_OPEN_CONNECTION;
        error = false;
    } else if (commandString.compare("add") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_ADD;
        commandstream >> psendMsg->itemName >> psendMsg->description >> psendMsg->price;
        error = commandstream.good();
    } else if (commandString.compare("update") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_UPDATE;
        commandstream >> psendMsg->itemID >> psendMsg->itemName >> psendMsg->description >> psendMsg->price;
        error = commandstream.good();
    } else if (commandString.compare("list") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_LIST;
        error = false;
    } else if (commandString.compare("details") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_DETAILS;
        commandstream >> psendMsg->itemID;
        error = commandstream.good();
    } else if (commandString.compare("close") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_CLOSE_CONNECTION;
        error = false;
    } else {
        cout << " -> open {void}" << endl;
        cout << "      Opens a new connection with the server" << endl;
        cout << " -> add {itemname} {description} {price}" << endl;
        cout << "      Adds an item with the given specification" << endl;
        cout << " -> list {void}" << endl;
        cout << "      Lists all the items" << endl;
        cout << " -> close {void}" << endl;
        cout << "      Closes the active connection and exits" << endl;
    }

    return error;
}

void doServerProcess() {
    cIPCIntf* ipcIf = new cIPCIntf();
    struct ipcMsg rcvdMsg;
    struct ipcMsg sendMsg;
    bool noMoreClients = false;

    cout << "Server Start Up...." << endl;

    /* Open the IPC interface, and if opened continue */
    if (ipcIf->openIf("nosqlipc", CIPCINTF_OPEN_MODE_SERVER)) {

        cout << "IPC Opened, waiting for messages...." << endl;
        /* Open a new NoSQLStore */
        NoSQLStore* pNoSqlStore = new NoSQLStore();

        pNoSqlStore->keyValueStore->loadDataToMap();

        /* While we can connect to at-least one client */
        while (ipcIf->connectIf()) {

            cout << endl;

            /* Get the next message from the connected client */
            if (ipcIf->getMsg(&rcvdMsg)) {
                /* Handle the received messages from the connected client in the server */
                noMoreClients = handleServerCommands(pNoSqlStore, rcvdMsg, &sendMsg);
                /* Send reply to the connected client */
                ipcIf->sendMsg(&sendMsg);
                /* Disconnect the client interface */
                ipcIf->disConnectIf();
            }

            if (noMoreClients == true) {
                break;
            }
        }

        pNoSqlStore->getKeyValueStore()->loadDataToFile();

        cout << "Server Shutdown...." << endl;
        /* Close before exit */
        ipcIf->closeIf(true);

    }
}

void doClientProcess() {
    cIPCIntf* ipcIf = new cIPCIntf();
    struct ipcMsg rcvdMsg;
    struct ipcMsg sendMsg;
    string command;
    bool error = false;
    bool closed = false;
    int connectionID = -1;

    cout << "Client Start Up...." << endl;

    /* Client processing loop */
    while (1) {
        /* Get the next command from user */
        do {
            cout << endl << ">>";
            getline(cin, command);
            error = parseCommand(command, &sendMsg);
        } while (error == true);

        /* Open the IPC to communicate with the server */
        if (ipcIf->openIf("nosqlipc", CIPCINTF_OPEN_MODE_CLIENT)) {
            /* Set the connection id */
            sendMsg.connectionID = connectionID;
            /* Send message to server */
            ipcIf->sendMsg(&sendMsg);

            /* Read message from server */
            if (ipcIf->getMsg(&rcvdMsg)) {

                /* Handle the received reply from server */
                closed = handleClientCommands(rcvdMsg, &connectionID);
                /* Close IPC */
                ipcIf->closeIf(false);

                if (closed) {
                    break;
                }
            } else {
                cout << "Error Opening IPC";
                break;
            }
        }
    }

    /* Close IPC */
    ipcIf->closeIf(true);
}

bool handleServerCommands(NoSQLStore* pNoSqlStore, struct ipcMsg rcvdMsg, struct ipcMsg* pSendMsg) {

    bool noMoreClients = false;
    int commandID = rcvdMsg.commandID;
    int connectionID = rcvdMsg.connectionID;

    pSendMsg->replyStatus = 1;
    pSendMsg->commandID = commandID;
    pSendMsg->connectionID = connectionID;

    switch (commandID) {

        case NOSQL_DATABASE_OPEN_CONNECTION:
        {
            pSendMsg->connectionID = pNoSqlStore->openConnection();
            pSendMsg->replyStatus = 0;
            cout << "Open Request has been received from the client : " << pSendMsg->connectionID << endl;
        }
            break;

        case NOSQL_DATABASE_CLOSE_CONNECTION:
        {
            cout << "Close Request has been received from the client : " << connectionID << endl;
            pNoSqlStore->closeConnection(connectionID);
            pSendMsg->replyStatus = 0;

            if (pNoSqlStore->numberOfConnections == 0) {
                noMoreClients = true;
            }
        }
            break;

        case NOSQL_DATABASE_ADD:
        {
            cout << "Add Item Request has been received from the client : " << connectionID << endl;
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            Item* item = new Item();
            item->setName(rcvdMsg.itemName);
            item->setDescription(rcvdMsg.description);
            item->setPrice(rcvdMsg.price);
            string addedItem = connection->addItem(item);
            pSendMsg->replyStatus = 0;
            mem[0] = NOSQL_DATABASE_NOTIFY_ADD;
            mem[1] = (char) (pNoSqlStore->notificationCount + 1);
            pNoSqlStore->notificationCount++;
            strcpy(&mem[2], addedItem.c_str());
        }
            break;

        case NOSQL_DATABASE_UPDATE:
        {
            cout << "Update Item Request has been received from the client : " << connectionID << endl;
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            Item* item = new Item();
            item->setItemID(rcvdMsg.itemID);
            item->setName(rcvdMsg.itemName);
            item->setDescription(rcvdMsg.description);
            item->setPrice(rcvdMsg.price);
            string updatedItem = connection->updateItem(item);
            cout << item->getDescription();
            pSendMsg->replyStatus = 0;
            mem[0] = NOSQL_DATABASE_NOTIFY_UPDATE;
            mem[1] = (char) (pNoSqlStore->notificationCount + 1);
            pNoSqlStore->notificationCount++;            
            strcpy(&mem[2], updatedItem.c_str());
        }
            break;

        case NOSQL_DATABASE_LIST:
        {
            cout << "List Item Request has been received from the client : " << connectionID << endl;
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            string returnValue = connection->listItem();
            pSendMsg->returnValue = returnValue;
            pSendMsg->replyStatus = 0;
        }
            break;

        case NOSQL_DATABASE_DETAILS:
        {
            cout << "Details Item Request has been received from the client : " << connectionID << endl;
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            string returnValue = connection->getItem(rcvdMsg.itemID);
            pSendMsg->returnValue = returnValue;
            pSendMsg->replyStatus = 0;
        }
            break;

        case NOSQL_DATABASE_ADD_EVENT:
        {
            cout << "Add Event Request has been received from the client : " << connectionID << endl;
            pSendMsg->replyStatus = 1;
        }
            break;

        case NOSQL_DATABASE_REMOVE_EVENT:
        {
            cout << "Remove Event Request has been received from the client : " << connectionID << endl;
            pSendMsg->replyStatus = 1;
        }
            break;

        default:
            cout << "Unknown command" << " from client" << endl;
            pSendMsg->replyStatus = 1;
    }

    return noMoreClients;
}

bool handleClientCommands(struct ipcMsg rcvdMsg, int* pConId) {
    bool closed = false;

    switch (rcvdMsg.commandID) {

        case NOSQL_DATABASE_OPEN_CONNECTION:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            cout << "Connection ID is  " << rcvdMsg.connectionID << endl;
            *pConId = rcvdMsg.connectionID;
            break;

        case NOSQL_DATABASE_CLOSE_CONNECTION:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            closed = true;
            break;

        case NOSQL_DATABASE_ADD:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            break;

        case NOSQL_DATABASE_UPDATE:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            break;

        case NOSQL_DATABASE_LIST:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            cout << rcvdMsg.returnValue;
            break;

        case NOSQL_DATABASE_DETAILS:
        {
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            cout << rcvdMsg.returnValue;
            break;
        }

        default:
            cout << "Unknown message from Server" << endl;
    }

    return closed;
}
