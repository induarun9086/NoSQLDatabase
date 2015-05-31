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

#include <map>

class KeyValueStore {
public:
    int numberOfItems;
    map<int, string> dataMap;
    
public:
    KeyValueStore();
    KeyValueStore(const KeyValueStore& orig);
    virtual ~KeyValueStore();
    
public:
    void intialize(string path);
    void addItem(Item* item);
    void manipulateItem(string key, string value);
    void listItems();
    void persist(string path);
    string serializeItem(Item* item);
    void deSerializeItem(string item);
    void loadDataToFile();
    void loadDataToMap();
};

#endif	/* KEYVALUESTORE_H */

