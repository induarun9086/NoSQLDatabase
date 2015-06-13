/*
 * NoSQLStore.cpp
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include "NoSQLStore.h"

NoSQLStore::NoSQLStore() {
    numberOfConnections = 0;
    nextConnectionId = 0;
    keyValueStore = new KeyValueStore();
    keyValueStore->numberOfItems = 0;
    notificationCount = 0;
    
}

int NoSQLStore::openConnection() {
    Connection* connection = new Connection(nextConnectionId,keyValueStore);
    connectionMap[nextConnectionId] = connection;
    numberOfConnections++;
    nextConnectionId++;
    return nextConnectionId - 1;
}

Connection* NoSQLStore::getConnection(int connectionID) {
    Connection* connection = connectionMap[connectionID];
    if (connection == NULL) {
        throw std::invalid_argument("Open connection and proceed");
    }
    return connection;
}

void NoSQLStore::closeConnection(int connectionID) {
    connectionMap.erase(connectionID);
    numberOfConnections--;
}

KeyValueStore* NoSQLStore::getKeyValueStore() {
    return keyValueStore;
}

int NoSQLStore:: getRegisteredConnections(int *pConnectionID,int notificationType)
{
    int count = 0;
    map<int, Connection*>::iterator iter;

        for (iter = connectionMap.begin(); iter != connectionMap.end(); ++iter) {
           Connection* connection = (Connection*)iter->second;
           if((notificationType == NOSQL_DATABASE_NOTIFY_ADD) && (connection->notifyAdd == true) )
           {
               pConnectionID[count] = connection->connectionID;
               count++ ;
               
           }
           else if((notificationType == NOSQL_DATABASE_NOTIFY_UPDATE) && (connection->notifyUpdate== true) )
           {
               pConnectionID[count] = connection->connectionID;
               count++ ;
               
           }
        }
    
               
        return count;
}

NoSQLStore::~NoSQLStore() {

}

        

