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

#define _OS_WINDOWS_ (defined(__CYGWIN__))
    
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

#define CIPCINTF_OPEN_MODE_SERVER (0)
#define CIPCINTF_OPEN_MODE_CLIENT (1)

using namespace std;

struct ipcMsg
{
    int connectionID;
    int commandID;
    int itemID;
    char itemName[32];
    char description[512];
    double price; 
    char event[10];
    int replyStatus;
    char returnValue[1024];
};

class cIPCIntf
{
public:
    cIPCIntf(void);
    ~cIPCIntf(void);
    bool openIf(string ifName, int openMode);
    bool connectIf(void);
    void disConnectIf(void);
    void closeIf(bool final);
    bool getMsg(struct ipcMsg* pIPCMsg);
    void sendMsg(struct ipcMsg* pIPCMsg);
    
private:
    bool ifState;
    int  mode;
    int  err;
    
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

