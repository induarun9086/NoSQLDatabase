/* 
 * File:   main.h
 * Author: indudinesh
 *
 * Created on 10 May, 2015, 11:29 AM
 */

#include <string>

using namespace std;

#ifndef MAIN_H
#define	MAIN_H

#define NOSQL_DATABASE_ADD ((int) 0)
#define NOSQL_DATABASE_UPDATE ((int) 1)
#define NOSQL_DATABASE_LIST ((int) 2)
#define NOSQL_DATABASE_OPEN_CONNECTION ((int)3)

bool parseCommand(string command,struct ipcMsg* psendMsg);

#endif	/* MAIN_H */

