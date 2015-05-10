/*
 * File:   ipc.c
 * Author: indudinesh
 *
 * Created on 9 May, 2015, 3:27 PM
 */

#include "ipc.hpp"

cIPCIntf::cIPCIntf()
{
    ifState = false;
}

cIPCIntf::~cIPCIntf()
{
    
}

bool cIPCIntf::openIf(string ifName, int openMode)
{   
#ifdef _OS_WINDOWS_    
    int numTries = 0;
#endif
    
    /* Assume as the interface is not opened */
    ifState = false;
    mode    = openMode;
    
#if _OS_WINDOWS_
    
    filePath  = TEXT("\\\\.\\pipe\\");
    filePath += ifName;
    
#elif _OS_MAC_X_
    
    ipFilePath  = "/tmp/ctos_";
    ipFilePath += ifName;
    opFilePath  = "/tmp/stoc_";
    opFilePath += ifName;
        
#endif
    
    /* Open as server */
    if(openMode == CIPCINTF_OPEN_MODE_SERVER)
    {
        
#if _OS_WINDOWS_

        /* Create the pipe */
        hPipe = CreateNamedPipe(filePath.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT,
                                PIPE_UNLIMITED_INSTANCES, 2048, 2048, 0, NULL);

        /* Validate pipe handle */
        if(hPipe == INVALID_HANDLE_VALUE)
        {
          cout << "Couldn't open the pipe for communication err:%d" << GetLastError() << endl;
        }
        else
        {
          /* Try to connect to the opened pipe, this is succeed when there are 
             clients listening to this pipe */
          ConnectNamedPipe(hPipe, NULL);
            
          /* Interface opened */
          ifState = true;
        }
        
#elif _OS_MAC_X_
        
        mkfifo(ipFilePath.c_str(), 0666);
        mkfifo(opFilePath.c_str(), 0666);
        
        cout << "Named pipes created..." << endl;
                
        hIpFile = open(ipFilePath.c_str(), O_RDONLY);
        hOpFile = open(opFilePath.c_str(), O_WRONLY);
        
        cout << "ip:" << hIpFile << "op:" << hOpFile << endl;
        
        if((hIpFile != -1) && (hOpFile != -1))
        {
            /* Interface opened */
            ifState = true;
        }
        else
        {
            cout << "Couldn't open the pipe for communication err:" << strerror(errno) << "(" << errno << ")" << endl;
        }
        
#endif
        
    }
    /* Open as client */
    else
    {
        
#if _OS_WINDOWS_
      /* Open the pipe */
      hPipe = CreateFile(filePath.c_str(), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

      /* If not opened wait and retry in loop */
      while(hPipe == INVALID_HANDLE_VALUE)
      {
        /* If error is not pipe busy, exit loop */
        if(GetLastError() != ERROR_PIPE_BUSY)
        {
          break;
        }
        else
        {
          /* Try to wait for the pipe */
          WaitNamedPipe(filePath.c_str(), NMPWAIT_USE_DEFAULT_WAIT);
        }

        /* Wait 1/2 sec */
        Sleep(500);
        numTries++;

        /* Retry to open */
        hPipe = CreateFile(filePath.c_str(), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
      }

      /* Validate pipe handle */
      if(hPipe == INVALID_HANDLE_VALUE)
      {
        cout << "Couldn't open the pipe for communication err:%d\n", GetLastError());
      }
      /* Valid handle available */
      else
      {
        /* Interface opened */
        ifState = true;
      }
#elif _OS_MAC_X_        
     
      hOpFile = open(ipFilePath.c_str(), O_WRONLY);
      hIpFile = open(opFilePath.c_str(), O_RDONLY);
      
      cout << "ip:" << hIpFile << "op:" << hOpFile << endl;

      if((hIpFile != -1) && (hOpFile != -1))
      {
          /* Interface opened */
          ifState = true;
      }
      else
      {
          cout << "Couldn't open the pipe for communication err:" << strerror(errno) << "(" << errno << ")" << endl;
      }
#endif
        
    }
    
    return ifState;
}

void cIPCIntf::closeIf()
{
    
#if _OS_WINDOWS_
    
  /* Disconnect & Close */
  DisconnectNamedPipe(hPipe);
  CloseHandle(hPipe);
  
#elif _OS_MAC_X_
  
  close(hIpFile);
  close(hOpFile);

  if(mode == CIPCINTF_OPEN_MODE_SERVER)
  {
    /* remove the FIFO */
    unlink(ipFilePath.c_str());
    unlink(opFilePath.c_str());
  }
  
#endif
  
}

bool cIPCIntf::getMsg(ipcMsg* pIPCMsg)
{
  bool msgAvai = true;
    
#if _OS_WINDOWS_
    
  int ipSize = 0;

  ReadFile(hPipe, pIPCMsg, sizeof(ipcMsg), &ipSize, NULL);
  
#elif _OS_MAC_X_

  int retSize;
  
  retSize = read(hIpFile, pIPCMsg, sizeof(ipcMsg));
  
#endif
  
  return msgAvai;
}

void cIPCIntf::sendMsg(ipcMsg* pIPCMsg)
{
    
#if _OS_WINDOWS_
    
  int ipSize = 0;
    
  WriteFile(hPipe, pIPCMsg, sizeof(ipcMsg), &opSize, NULL);
  
#elif _OS_MAC_X_
  
  int retSize;
  
  retSize = write(hOpFile, pIPCMsg, sizeof(ipcMsg));
  
#endif
}