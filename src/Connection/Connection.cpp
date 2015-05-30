/*
 * Connection.cpp
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include "Connection.h"
#include "../Item/Item.h"
#include "../KeyValueStore/KeyValueStore.h"



Connection::Connection(int connectionID) {
	// TODO Auto-generated constructor stub

}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

void Connection::addItem(Item* item)
{
    KeyValueStore* keyValueStore = new KeyValueStore();
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

