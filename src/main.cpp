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

                /* Get the next message */
                while (ipcIf->getMsg(&rcvdMsg)) {
                    
                    cout << "command received from client : " << rcvdMsg.commandID <<endl;

                    switch (rcvdMsg.commandID) {
                        case NOSQL_DATABASE_ADD:

                            break;
                        case NOSQL_DATABASE_UPDATE:

                            break;
                        case NOSQL_DATABASE_LIST:

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
                        
                        cout << "Reply Received from Server :" << rcvdMsg.replyStatus;

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
