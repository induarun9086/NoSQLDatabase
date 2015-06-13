/*
 * Connection.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#ifndef SRC_CONNECTION_CONNECTION_H_
#define SRC_CONNECTION_CONNECTION_H_

#include <string>
#include <stdexcept> 
#include "../Item/Item.h"
#include "../KeyValueStore/KeyValueStore.h"

using namespace std;

class Connection {
public:
	int connectionID;
        KeyValueStore* keyValueStore;
        bool notifyAdd;
        bool notifyUpdate;
        //string updateElements[];
public:
	Connection(int cID,KeyValueStore* keyValueStore);
	virtual ~Connection();

public:
	string getItem(int itemID);
	string addItem(Item* item);
	string updateItem(Item* item);
        string listItem();
	void registerEvent(string event);
	//void unregisterEvent(int);
};

#endif /* SRC_CONNECTION_CONNECTION_H_ */
