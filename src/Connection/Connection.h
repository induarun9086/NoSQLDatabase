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
public:
	Connection(int cID,KeyValueStore* keyValueStore);
	virtual ~Connection();

public:
	string getItem(int itemID);
	void addItem(Item* item);
	void updateItem(Item* item);
        string listItem();
	//int registerEvent(string);
	//void unregisterEvent(int);
};

#endif /* SRC_CONNECTION_CONNECTION_H_ */
