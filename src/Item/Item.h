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
public:
		string name;
		string des;
		int price;

public:
		Item();

public:
		void addItem();
		void showItem();
		void manipulateItem();

};

#endif  /* SRC_ITEM_ITEM_H_ */

