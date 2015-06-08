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
    pt.put("itemid", item->getItemID());
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

void KeyValueStore::loadDataToFile() {
    map<int, string>::iterator iter;
    ofstream newFile("data.txt");
    for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
        newFile << iter->first << ";" << iter->second;
    }
    newFile.close();
}

void KeyValueStore::loadDataToMap() {
    ifstream file("data.txt");

    char delimiter = ';';
    if (file.good()) {
        std::string str;
        while (std::getline(file, str)) {
            istringstream ss(str);
            string key;
            string value;
            getline(ss, key, delimiter);
            getline(ss, value, delimiter);
            cout << "key is " << atoi(key.c_str()) << endl;
            dataMap[atoi(key.c_str())] = value;
            lastItemID = dataMap.rbegin()->first;
        }
    } else {
        lastItemID = 0;
    }
    map<int, string>::iterator iter;

    for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
        cout << iter->first << ':' << iter->second << endl;
    }
}

void KeyValueStore::addItem(Item* item) {
    if (lastItemID != 0) {
        lastItemID = lastItemID + 1;
    }
    item->setItemID(lastItemID);
    lastItemID++;
    serializeItem(item);
}

void KeyValueStore::manipulateItem(Item* item) {
    int itemID = item->getItemID();

    string value = dataMap[itemID];
    if (value.empty()) {
        perror("Given ItemID does not exist");
    }
    serializeItem(item);
}

string KeyValueStore::getItem(int itemID) {
    string value;
    try {
        map<int, string>::iterator pos;
        pos = dataMap.find(itemID);

        if (pos == dataMap.end()) {

            value = "Item does not exists";

        } else {
            value = pos->second;
        }

    } catch (const exception& e) {

        cout << "Error occured while retriving data" << endl;
    }

    return value;

}

string KeyValueStore::listItems() {
    std::vector<string> list;
    map<int, string>::iterator iter;

    for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
        list.push_back(iter->second);
    }

    std::ostringstream oss;

    if (!list.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(list.begin(), list.end() - 1,
                std::ostream_iterator<string>(oss, ","));

        // Now add the last element with no delimiter
        oss << list.back();
    }

    return oss.str();

}



