/* 
 * File:   main.h
 * Author: indudinesh
 *
 * Created on 10 May, 2015, 11:29 AM
 */

#include <string>

#include "ipc/ipc.hpp"
#include "Item/Item.h"
#include "NoSQLStore/NoSQLStore.h"
#include "Connection/Connection.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost::interprocess;

#ifndef MAIN_H
#define	MAIN_H

#define NOSQL_DATABASE_ADD ((int) 0)
#define NOSQL_DATABASE_UPDATE ((int) 1)
#define NOSQL_DATABASE_LIST ((int) 2)
#define NOSQL_DATABASE_OPEN_CONNECTION ((int)3)
#define NOSQL_DATABASE_CLOSE_CONNECTION ((int)4)
#define NOSQL_DATABASE_ADD_EVENT ((int)5)
#define NOSQL_DATABASE_REMOVE_EVENT ((int)6)
#define NOSQL_DATABASE_DETAILS ((int) 7)


struct notificationMsg
{
    int notificationID;
    int count;
    int numberOfClients;
    int connectionID[200];
    char itemDetails[1024];
};

struct sharedMem
{
    shared_memory_object shm;
    mapped_region region;
};

bool parseCommand(string command,struct ipcMsg* psendMsg);
void doServerProcess();
bool handleServerCommands(NoSQLStore* pNoSqlStore, struct ipcMsg rcvdMsg, struct ipcMsg* pSendMsg);
void doClientProcess();
bool handleClientCommands(struct ipcMsg rcvdMsg, int* pConId);

char* createSharedMemoryRW(const char* name,int size);
char* createSharedMemoryRO(const char* name);

#endif	/* MAIN_H */

