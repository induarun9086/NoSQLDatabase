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

#include "main.h"
#include "ipc/ipc.hpp"
#include "Item/Item.h"
#include "NoSQLStore/NoSQLStore.h"

using namespace std;

int main(int argc, char* argv[]) {
    cIPCIntf* ipcIf = new cIPCIntf();
    struct ipcMsg rcvdMsg;
    struct ipcMsg sendMsg;

    /* Validate the number of arguments */
    if (argc < 2) {
        cout << "Provide argument s for server or c for client" << endl;
    } else {
        /* If option s is given then we should run in server mode */
        if (argv[1][0] == 's') {
            cout << "Server Start Up...." << endl;
            /* Open the IPC interface, and if opened continue */
            if (ipcIf->openIf("nosqlipc", CIPCINTF_OPEN_MODE_SERVER)) {
                cout << "IPC Opened, waiting for messages...." << endl;
                NoSQLStore* nosqlStore = new NoSQLStore();
                /* Get the next message */
                while (ipcIf->getMsg(&rcvdMsg)) {

                    cout << "command received from client : " << rcvdMsg.commandID << endl;

                    int commandID = rcvdMsg.commandID;
                    sendMsg.replyStatus = 1;
                    sendMsg.commandID = commandID;

                    switch (commandID) {
                        case NOSQL_DATABASE_OPEN_CONNECTION:
                            sendMsg.connectionID = nosqlStore->openConnection();
                            sendMsg.replyStatus = 0;
                            break;
                        case NOSQL_DATABASE_ADD:
                        {
                            int connectionID = sendMsg.connectionID;
                            Connection* connection = nosqlStore->connectionMap[connectionID];
                            if (connection != NULL) {
                                cout << "Add Item Request has been received from the client : " << connectionID << endl;
                                connection->addItem();
                            } else {
                                cout << "Connection has not opened.Open connetion and call add item" << endl;
                            }

                        }
                            break;
                        case NOSQL_DATABASE_UPDATE:
                        {
                            int connectionID = sendMsg.connectionID;
                            Connection* connection = nosqlStore->connectionMap[connectionID];
                            if (connection != NULL) {
                                cout << "Update Item Request has been received from the client : " << connectionID << endl;
                                connection->updateItem();
                            } else {
                                cout << "Connection has not opened.Open connetion and call update item" << endl;
                            }

                        }
                            break;
                        case NOSQL_DATABASE_LIST:
                        {
                            int connectionID = sendMsg.connectionID;
                            Connection* connection = nosqlStore->connectionMap[connectionID];
                            if (connection != NULL) {
                                cout << "Update Item Request has been received from the client : " << connectionID << endl;
                                connection->getItem();
                            } else {
                                cout << "Connection has not opened.Open connetion and call update item" << endl;
                            }
                        }
                            break;
                        default:
                            cout << "Unknown message from client" << endl;
                    }



                    /* Send reply to client */
                    ipcIf->sendMsg(&sendMsg);

                    /* Wait 1 sec */
                    //boost::this_thread::sleep(boost::posix_time::seconds(1));
                }

                cout << "Server Shutdown...." << endl;

                /* Close before exit */
                ipcIf->closeIf();
            }
        } else
            /* Else in client mode */ {
            cout << "Client Start Up...." << endl;

            if (ipcIf->openIf("nosqlipc", CIPCINTF_OPEN_MODE_CLIENT)) {


                do {
                    cout << ">>";
                    cin >> sendMsg.commandID;

                    /* Send message to server */
                    ipcIf->sendMsg(&sendMsg);

                    /* Read message from server */
                    if (ipcIf->getMsg(&rcvdMsg)) {

                        switch (rcvdMsg.commandID) {
                            case NOSQL_DATABASE_OPEN_CONNECTION:
                                cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
                                cout << "Connection ID is  " << rcvdMsg.connectionID << endl;


                                break;

                            case NOSQL_DATABASE_ADD:

                                cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;

                                break;
                            case NOSQL_DATABASE_UPDATE:
                                cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;

                                break;
                            case NOSQL_DATABASE_LIST:
                                cout << "Reply Received from Server : " << rcvdMsg.replyStatus << endl;
                                break;
                            default:
                                cout << "Unknown message from client" << endl;

                                cout << "Reply Received from Server :" << rcvdMsg.replyStatus;
                        }

                        /* Wait 1 sec */
                        //boost::this_thread::sleep(boost::posix_time::seconds(1));
                    } else {
                        break;
                    }
                } while (1);

                /* Close before exit */
                ipcIf->closeIf();
            }
        }
    }
    return 0;
}
