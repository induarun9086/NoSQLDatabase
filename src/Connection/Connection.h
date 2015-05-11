/*
 * Connection.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#ifndef SRC_CONNECTION_CONNECTION_H_
#define SRC_CONNECTION_CONNECTION_H_

#include <string>

using namespace std;

class Connection {
public:
	int connectionID;
public:
	Connection(int connectionID);
	virtual ~Connection();

public:
	void getItem();
	void addItem();
	void updateItem();
	//int registerEvent(string);
	//void unregisterEvent(int);
};

#endif /* SRC_CONNECTION_CONNECTION_H_ */
