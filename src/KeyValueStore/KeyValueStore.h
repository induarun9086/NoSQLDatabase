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
    int lastItemID;
    
public:
    KeyValueStore();
    KeyValueStore(const KeyValueStore& orig);
    virtual ~KeyValueStore();
    
public:
    void addItem(Item* item);
    void manipulateItem(Item* item);
    string getItem(int itemID);
    string listItems();
    string serializeItem(Item* item);
    void loadDataToFile();
    void loadDataToMap();
};

#endif	/* KEYVALUESTORE_H */

