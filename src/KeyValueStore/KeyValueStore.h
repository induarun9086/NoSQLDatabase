/* 
 * File:   KeyValueStore.h
 * Author: indudinesh
 *
 * Created on 12 May, 2015, 11:43 AM
 */

#ifndef KEYVALUESTORE_H
#define	KEYVALUESTORE_H

#include <string>

using namespace std;

class KeyValueStore {
public:
    int numberOfItems;
public:
    KeyValueStore();
    KeyValueStore(const KeyValueStore& orig);
    virtual ~KeyValueStore();
public:
    void intialize(string path);
    string get(string key);
    void put (string key,string value);
    void persist(string path);
};

#endif	/* KEYVALUESTORE_H */

