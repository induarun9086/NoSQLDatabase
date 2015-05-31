/*
 * NoSQLStore.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#ifndef SRC_NOSQLSTORE_NOSQLSTORE_H_
#define SRC_NOSQLSTORE_NOSQLSTORE_H_

#include <string>
#include <map>

#include "../Connection/Connection.h"
#include "../KeyValueStore/KeyValueStore.h"

using namespace std;

class NoSQLStore {
public:
	int numberOfConnections;
        int nextConnectionId;
        map<int,Connection*> connectionMap;
        KeyValueStore* keyValueStore;

public:
	NoSQLStore();
	virtual ~NoSQLStore();

public:
	int openConnection();
	void closeConnection(int);
	Connection* getConnection(int);
	//Connection getKeyValueStore();
        //void evaluateChange(int,string,string);
        KeyValueStore* getKeyValueStore();

};

#endif /* SRC_NOSQLSTORE_NOSQLSTORE_H_ */
