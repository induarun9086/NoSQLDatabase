/*
 * Item.h
 *
 *  Created on: 03-May-2015
 *      Author: indudinesh
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include <boost/uuid/uuid.hpp>          // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>        // streaming operators etc.

#include "Item.h"

using namespace std;

Item::Item() {
}

void Item::setItemID(int id) {
    itemID = id;
}

void Item::setName(string name) {
    itemName = name;
}

void Item::setDescription(string description) {
    itemDescription = description;
}

void Item::setPrice(double price) {
    itemPrice = price;
}

int Item::getItemID() {
    return itemID;
}

string Item::getName() {
    return itemName;
}

string Item::getDescription() {
    return itemDescription;
}

double Item::getPrice() {
    return itemPrice;
}