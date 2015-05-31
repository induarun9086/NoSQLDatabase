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

void Connection::addItem(Item* item)
{
    keyValueStore->addItem(item);
}

/*void Connection::updateItem()
{
    Item* i = new Item();
    //i->manipulateItem();
}

void Connection::getItem()
{
    Item* i = new Item();
    //i->showItem();
}*/

