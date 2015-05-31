/*
 * Item.h

 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#ifndef SRC_ITEM_ITEM_H_
#define SRC_ITEM_ITEM_H_

#include <string>

using namespace std;

class Item {
private:
    int itemID;
    string itemName;
    string itemDescription;
    double itemPrice;

public:
    Item();

public:
    void setItemID(int id);
    int getItemID();
    void setName(string name);
    string getName();
    void setDescription(string description);
    string getDescription();
    void setPrice(double price);
    double getPrice();

};

#endif  /* SRC_ITEM_ITEM_H_ */

