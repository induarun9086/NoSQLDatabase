/* 
 * File:   KeyValueStore.cpp
 * Author: indudinesh
 * 
 * Created on 12 May, 2015, 11:43 AM
 */

#include "KeyValueStore.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

KeyValueStore::KeyValueStore() {
}

KeyValueStore::KeyValueStore(const KeyValueStore& orig) {
}

KeyValueStore::~KeyValueStore() {
}

string KeyValueStore::serializeItem(Item* item) {
    ptree pt;
    pt.put("name", item->getName());
    pt.put("description", item->getDescription());
    pt.put("price", item->getPrice());
    std::ostringstream buf;
    boost::property_tree::write_json(buf, pt, false);
    std::string json = buf.str();
    dataMap[item->getItemID()] = json;
    numberOfItems++;
    loadDataToFile();
    return json;
}

void KeyValueStore::deSerializeItem(string itemString) {
    /* ptree pt;
     boost::property_tree::read_json(itemString, pt, false);
     Item i;
     i.setName(pt.get_value("name"));
     i.setDescription(pt.get_value("description"));
     i.setPrice((double)pt.get_value("price"));*/

}

void KeyValueStore::loadDataToFile() {
    map<int, string>::iterator iter;
    ofstream newFile("data.txt");
    for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
        newFile << iter->first << " : " << iter->second
                << endl;
    }
    newFile.close();
}

void KeyValueStore::loadDataToMap() {
    ofstream outfile;
    //outfile.open("afile.dat");
}

void KeyValueStore::addItem(Item* item) {
    item->setItemID(numberOfItems);
    serializeItem(item);
}



