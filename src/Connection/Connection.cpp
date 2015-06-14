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
    notifyAdd = false;
    notifyUpdate = false;
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

void Connection::listItem(struct itemList* pList)
{
     keyValueStore->listItems(pList);
}

void Connection::registerEvent(string event)
{
    if(event.compare("add") == 0)
    {
        notifyAdd = true;
    }
    else if(event.compare("update") == 0)
    {
        notifyUpdate = true;
    }
    else
    {
        throw std::invalid_argument( "Invalid event provided" );
    }
}

void Connection::unRegisterEvent(string event)
{
    if(event.compare("add") == 0)
    {
        notifyAdd = false;
    }
    else if(event.compare("update") == 0)
    {
        notifyUpdate = false;
    }
    else
    {
        throw std::invalid_argument( "Invalid event provided" );
    }
}

