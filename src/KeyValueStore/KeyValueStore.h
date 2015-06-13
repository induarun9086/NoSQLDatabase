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
    string addItem(Item* item);
    string manipulateItem(Item* item);
    string getItem(int itemID);
    void listItems(struct itemList* pList);
    string serializeItem(Item* item);
    void loadDataToFile();
    void loadDataToMap();
};

#endif	/* KEYVALUESTORE_H */

