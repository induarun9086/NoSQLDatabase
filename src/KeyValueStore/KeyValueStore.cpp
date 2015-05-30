/* 
 * File:   KeyValueStore.cpp
 * Author: indudinesh
 * 
 * Created on 12 May, 2015, 11:43 AM
 */

#include "KeyValueStore.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

KeyValueStore::KeyValueStore() {
}

KeyValueStore::KeyValueStore(const KeyValueStore& orig) {
}

KeyValueStore::~KeyValueStore() {
}

void KeyValueStore::serializeItem(Item* item) {
    ptree pt;
    pt.put("name", item->getName());
    pt.put("description", item->getDescription());
    pt.put("price", item->getPrice());
    std::ostringstream buf;
    boost::property_tree::write_json(buf, pt, false);
    std::string json = buf.str();
    cout << json;
}

void KeyValueStore::addItem(Item* item) {

    serializeItem(item);

}


