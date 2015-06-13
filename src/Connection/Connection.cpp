/*
 * Connection.cpp
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include "Connection.h"
#include "../Item/Item.h"
#include "../KeyValueStore/KeyValueStore.h"



Connection::Connection(int cID,KeyValueStore* kvStore) {
    connectionID = cID;
    keyValueStore = kvStore;
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

string Connection::addItem(Item* item)
{
    return keyValueStore->addItem(item);
}

string Connection::updateItem(Item* item)
{
    return keyValueStore->manipulateItem(item);
}

string Connection::getItem(int itemID)
{
    return keyValueStore->getItem(itemID);
}

string Connection::listItem()
{
    return keyValueStore->listItems();
}

