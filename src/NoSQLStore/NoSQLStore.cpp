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

NoSQLStore::~NoSQLStore() {

}
