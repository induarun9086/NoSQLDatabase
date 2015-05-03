/*
 * NoSQLStore.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#ifndef SRC_NOSQLSTORE_NOSQLSTORE_H_
#define SRC_NOSQLSTORE_NOSQLSTORE_H_

#include <string>
#include "../Connection/Connection.h"

using namespace std;

class NoSQLStore {
public:
	int numberOfConnections;

public:
	NoSQLStore();
	virtual ~NoSQLStore();

public:
	int openConnection();
	void closeConnection(int);
	Connection getConnection(int);
	Connection getKeyValueStore();
	void evaluateChange(int,string,string);

};

#endif /* SRC_NOSQLSTORE_NOSQLSTORE_H_ */