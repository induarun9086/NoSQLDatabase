/* 
 * File:   newsimpletest1.cpp
 * Author: indudinesh
 *
 * Created on 15 Jun, 2015, 6:19:09 PM
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NoSQLTest


#include <stdlib.h>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../../src/KeyValueStore/KeyValueStore.h"
#include "../../src/Item/Item.h"
#include "../../src/Connection/Connection.h"
#include "../../src/NoSQLStore/NoSQLStore.h"


string testAddItem() {
    Item* item = new Item();
    item->setItemID(0);
    item->setName("pen");
    item->setDescription("to write");
    item->setPrice(30.0);
    
    KeyValueStore* kvStore = new KeyValueStore();
    std::string result = kvStore->addItem(item);
    return result;
    
}

string testUpdateItem() {
    Item* item = new Item();
    item->setItemID(1);
    item->setName("pen1");
    item->setDescription("to write");
    item->setPrice(40.0);
    
    KeyValueStore* kvStore = new KeyValueStore();
    std::string result = kvStore->addItem(item);
    
    item->setItemID(1);
    item->setName("pen1");
    item->setDescription("to write");
    item->setPrice(50.0);
    
    result = kvStore->manipulateItem(item);
    
    return result;
   
}

void  testRegisterEvent(Connection* connection,string event)
{
    connection->registerEvent(event);
}

void  testunRegisterEvent(Connection* connection,string event)
{
    connection->unRegisterEvent(event);
}

BOOST_AUTO_TEST_CASE(NoSQLTest)
{
    // Test add Item
    std::string addResult = "{\"itemid\":\"0\",\"name\":\"pen\",\"description\":\"to write\",\"price\":\"30\"}\n";
    
    std::string result = testAddItem();
    
    BOOST_CHECK(result.compare(addResult) == 0);
    
    // Test update Item
    std::string updateResult = "{\"itemid\":\"1\",\"name\":\"pen1\",\"description\":\"to write\",\"price\":\"50\"}\n";

    result = testUpdateItem();
    
    BOOST_CHECK(result.compare(updateResult) == 0);
    
    // Test Register Event for add
    NoSQLStore* pNoSqlStore = new NoSQLStore();
    
    int connectionID = pNoSqlStore->openConnection(); 
    
    Connection* connection = pNoSqlStore->getConnection(connectionID);
    
    testRegisterEvent(connection,"add");
        
    BOOST_CHECK(connection->notifyAdd == true);
    
    // Test Register Event for update  
    testRegisterEvent(connection,"update"); 
        
    BOOST_CHECK(connection->notifyUpdate == true);
        
    
    // Test unRegister Event for add   
    testunRegisterEvent(connection,"add"); 
        
    BOOST_CHECK(connection->notifyAdd == false);
    
    
    // Test unRegister Event for update   
    testunRegisterEvent(connection,"update"); 
        
    BOOST_CHECK(connection->notifyUpdate == false);
}

