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

NoSQLStore::~NoSQLStore()
{
    
}
