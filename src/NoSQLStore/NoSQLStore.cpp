/*
 * NoSQLStore.cpp
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include "NoSQLStore.h"

NoSQLStore::NoSQLStore() {
    numberOfConnections = 0;
}

int NoSQLStore::openConnection() {
    Connection* connection = new Connection(numberOfConnections);
    connectionMap[numberOfConnections] = connection;
    numberOfConnections++;
    return numberOfConnections - 1;
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
}

KeyValueStore* NoSQLStore::getKeyValueStore() {

    return new KeyValueStore();

}

NoSQLStore::~NoSQLStore() {

}
