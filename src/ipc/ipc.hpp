/* 
 * File:   ipc.hpp
 * Author: indudinesh
 *
 * Created on 9 May, 2015, 3:21 PM
 */

#ifndef IPC_HPP
#define	IPC_HPP

#include <iostream>
#include <cstdlib>
#include <string>

#define _OS_WINDOWS_ ((_WIN32) || (_WIN64))
    
#define _OS_MAC_X_   ((__APPLE__) && (__MACH__))

#if _OS_WINDOWS_
#include <windows.h>
#elif _OS_MAC_X_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#else
#error "Unsupported OS"
#endif

#include <boost/thread/thread.hpp>

#define CIPCINTF_OPEN_MODE_SERVER (0)
#define CIPCINTF_OPEN_MODE_CLIENT (1)

using namespace std;

struct ipcMsg
{
    int connectionID;
    int commandID;
    int itemID;
    string itemName;
    string description;
    int quantity;
    double price; 
    int replyStatus;
};

class cIPCIntf
{
public:
    cIPCIntf(void);
    ~cIPCIntf(void);
    bool openIf(string ifName, int openMode);
    void closeIf(void);
    bool getMsg(struct ipcMsg* pIPCMsg);
    void sendMsg(struct ipcMsg* pIPCMsg);
    
private:
    bool ifState;
    int  mode;
    
#if _OS_WINDOWS_
  string filePath;
  HANDLE hPipe;
#elif _OS_MAC_X_
  string ipFilePath;
  string opFilePath;
  int hIpFile;
  int hOpFile;
#endif
};

#endif	/* IPC_HPP */

