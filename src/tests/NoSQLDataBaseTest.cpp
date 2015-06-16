/* 
 * File:   NosqlDataBaseTest.cpp
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

Connection* connection;
NoSQLStore* pNoSqlStore;

void openConnection()
{
    pNoSqlStore = new NoSQLStore();

    int connectionID = pNoSqlStore->openConnection(); 
    
    connection = pNoSqlStore->getConnection(connectionID);
    
}

void closeConnection()
{
    int connectionID = connection->connectionID;
    pNoSqlStore->closeConnection(connectionID);
}

struct F {
    F()  { openConnection();}
   ~F() { closeConnection(); }

};

string testAddItem() {
    Item* item = new Item();
    item->setName("pen");
    item->setDescription("to write");
    item->setPrice(30.0);
    connection->addItem(item); 
    
    KeyValueStore* kvStore = new KeyValueStore();
    std::string result = kvStore->addItem(item);
    return result;
    
}

string testUpdateItem() {
    Item* item = new Item();
    item->setName("pen1");
    item->setDescription("to write");
    item->setPrice(40.0);
    
    KeyValueStore* kvStore = new KeyValueStore();
    kvStore->addItem(item);
    
    item->setItemID(0);
    item->setName("pen1");
    item->setDescription("to write");
    item->setPrice(50.0);
    
    std::string result = kvStore->manipulateItem(item);
    
    return result;
   
}

void  testRegisterAddEvent()
{
    connection->registerEvent("add");
}

void  testRegisterUpdateEvent()
{
    connection->registerEvent("update");
}

void  testunRegisterEventUpdate()
{
    connection->unRegisterEvent("add");
}


BOOST_FIXTURE_TEST_SUITE( NoSQLTest,F )

BOOST_AUTO_TEST_CASE( addItem )
{
    // Test add Item
    std::string addResult = "{\"itemid\":\"0\",\"name\":\"pen\",\"description\":\"to write\",\"price\":\"30\"}\n";
    
    std::string result = testAddItem();
    
    BOOST_CHECK(result.compare(addResult) == 0);
}

BOOST_AUTO_TEST_CASE( updateItem )
{
    // Test update Item
    std::string updateResult = "{\"itemid\":\"0\",\"name\":\"pen1\",\"description\":\"to write\",\"price\":\"50\"}\n";

    std::string result = testUpdateItem();
    
    BOOST_CHECK(result.compare(updateResult) == 0);
}

BOOST_AUTO_TEST_CASE( registerEventAdd )
{
    // test register event for add
    testRegisterAddEvent();
    BOOST_CHECK(connection->notifyAdd == true);
}

BOOST_AUTO_TEST_CASE( registerEventUpdate )
{
    // test register event for update
    testRegisterUpdateEvent();
    BOOST_CHECK(connection->notifyUpdate == true);
}

BOOST_AUTO_TEST_CASE( unregisterEventAdd )
{
    // test unregister event for add
    testunRegisterEventUpdate();
    BOOST_CHECK(connection->notifyAdd == false);
}

BOOST_AUTO_TEST_CASE( unregisterEventUpdate )
{
    // test unregister event for update
    testunRegisterEventUpdate();
    BOOST_CHECK(connection->notifyUpdate == false);
}

BOOST_AUTO_TEST_SUITE_END()

