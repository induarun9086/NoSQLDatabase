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

using namespace boost::interprocess;

struct sharedMem listSharedMem;
struct sharedMem notificationSharedMem;
char* plistMemory;
char* pNotificationMemory;
int connectionID = -1;

using namespace std;

void notify_thread() {
    int currentCount = 0;
    const struct notificationMsg* pNotificationMsg;
    bool matchFound = false;

    while (1) {
        matchFound = false;
        sleep(1);
        
        pNotificationMsg = (const struct notificationMsg*) pNotificationMemory;
        if (currentCount != pNotificationMsg->count) {
            currentCount = pNotificationMsg->count;   

            for (int i = 0; i < pNotificationMsg->numberOfClients; i++)
            {
                if (connectionID == pNotificationMsg->connectionID[i]) {
                    
                    matchFound = true;
                }

            }
            if (matchFound) {
                if (pNotificationMsg->notificationID == NOSQL_DATABASE_NOTIFY_ADD) {
                    cout << "Item has been added" << endl << &pNotificationMsg->itemDetails[0] << endl << ">>" << endl;
                }


                if (pNotificationMsg->notificationID == NOSQL_DATABASE_NOTIFY_UPDATE) {
                    cout << "Item has been updated" << endl << &pNotificationMsg->itemDetails[0] << endl << ">>" << endl;
                }
            }
        }


    }

}

char* createSharedMemory(struct sharedMem* pShm, const char* name,int size,int access)
{
    if(access == 0)
    {
        pShm->shm = shared_memory_object(open_or_create, name, read_write);
    }
    else //if(access == 1)
    {
        pShm->shm = shared_memory_object(open_or_create, name, read_only);
    }
    
    if(size != 0)
    {
        //Set size
        pShm->shm.truncate(size);
    }
    //Map the whole shared memory in this process
    if(access == 0)
    {
        pShm->region = mapped_region(pShm->shm, read_write);
    }
    else //if(access == 1)
    {
        pShm->region = mapped_region(pShm->shm, read_only);
    }

    if(size != 0)
    {
        //Write all the memory to 0
        memset(pShm->region.get_address(), 0, pShm->region.get_size());
    }

    return static_cast<char*>(pShm->region.get_address());
}

int main(int argc, char* argv[]) {
    /* Validate the number of arguments */
    if (argc < 2) {
        cout << "Provide argument s for server or c for client" << endl;
    } else {
        /* If option s is given then we should run in server mode */
        if (argv[1][0] == 's') {
            pNotificationMemory = createSharedMemory(&notificationSharedMem, "Notification",2048,0);
            plistMemory = createSharedMemory(&listSharedMem, "List",104800,0);
            if((pNotificationMemory != NULL) && (plistMemory != NULL))
            {
                doServerProcess();
            }
        } else /* Else in client mode */ {
            pNotificationMemory = createSharedMemory(&notificationSharedMem, "Notification",0,1);
            plistMemory = createSharedMemory(&listSharedMem, "List",0,1);
            if((pNotificationMemory != NULL) && (plistMemory != NULL))
            {
                boost::thread workerThread(notify_thread);
                doClientProcess();
            }
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
    }
    else if (commandString.compare("event") == 0) {
        psendMsg->commandID = NOSQL_DATABASE_ADD_EVENT;
        commandstream >> psendMsg->event;
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


    cout << "Client Start Up...." << endl;

    /* Client processing loop */
    while (1) {
        /* Get the next command from user */
        do {
            cout << endl << ">> ";
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
    struct notificationMsg notificationMsg;

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
            notificationMsg.notificationID = NOSQL_DATABASE_NOTIFY_ADD;
            notificationMsg.count = (char) (pNoSqlStore->notificationCount + 1);
            pNoSqlStore->notificationCount++;
            strcpy(&notificationMsg.itemDetails[0], addedItem.c_str());
            notificationMsg.numberOfClients =
                    pNoSqlStore->getRegisteredConnections(&notificationMsg.connectionID[0], NOSQL_DATABASE_NOTIFY_ADD);
            memcpy(pNotificationMemory, &notificationMsg, sizeof (notificationMsg));
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
            pSendMsg->replyStatus = 0;

            notificationMsg.notificationID = NOSQL_DATABASE_NOTIFY_UPDATE;
            notificationMsg.count = (char) (pNoSqlStore->notificationCount + 1);
            pNoSqlStore->notificationCount++;
            strcpy(&notificationMsg.itemDetails[0], updatedItem.c_str());
            notificationMsg.numberOfClients =
                    pNoSqlStore->getRegisteredConnections(&notificationMsg.connectionID[0], NOSQL_DATABASE_NOTIFY_UPDATE);
            memcpy(pNotificationMemory, &notificationMsg, sizeof (notificationMsg));
        }
            break;

        case NOSQL_DATABASE_LIST:
        {
            cout << "List Item Request has been received from the client : " << connectionID << endl;
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            struct itemList* pList = (struct itemList*)plistMemory;
            connection->listItem(pList);
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
            string event(rcvdMsg.event);
            Connection* connection = pNoSqlStore->getConnection(connectionID);
            connection->registerEvent(event);
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
        {
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            struct itemList* pList =  (struct itemList*) plistMemory;

            cout << "List of items:" << endl << endl;
            for(int i = 0; i < pList->numberOfItems;i++)
            {
                cout << pList->itemData[i] << endl;
            }
            break;
        }

        case NOSQL_DATABASE_DETAILS:
        {
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            cout << rcvdMsg.returnValue;
            break;
        }

        case NOSQL_DATABASE_ADD_EVENT:
            cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
            break;
        default:
            cout << "Unknown message from Server" << endl;
    }

    return closed;
}
