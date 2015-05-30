/* 
 * File:   KeyValueStore.h
 * Author: indudinesh
 *
 * Created on 12 May, 2015, 11:43 AM
 */

#ifndef KEYVALUESTORE_H
#define	KEYVALUESTORE_H

#include <string>
#include "../Item/Item.h"

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
    void addItem(Item* item);
    void manipulateItem (string key,string value);
    void listItems();
    void persist(string path);
    void serializeItem(Item* item);
};

#endif	/* KEYVALUESTORE_H */

