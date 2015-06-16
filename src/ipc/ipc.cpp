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
    
    /* Copy and save the mode */
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
          cout << "Couldn't open the pipe for communication err:" << GetLastError() << endl;
        }
        else
        {
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
      while((hPipe == INVALID_HANDLE_VALUE) && (numTries < 1200))
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
        cout << "Couldn't open the pipe for communication err:" << GetLastError();
      }
      /* Valid handle available */
      else
      {
        /* Interface opened */
        ifState = true;
      }
      
#elif _OS_MAC_X_        
     
      if(ifState == false) 
      {
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
      }  
      
#endif
        
    }
    
    return ifState;
}

bool cIPCIntf::connectIf(void)
{
    bool connected = false;
    
#if _OS_WINDOWS_
    
    /* Open as server */
    if(mode == CIPCINTF_OPEN_MODE_SERVER)
    { 
        /* Try to connect to the opened pipe, this is succeed when there are 
           clients listening to this pipe */
        connected = ConnectNamedPipe(hPipe, NULL);
        
        /* If not connected */
        if(!connected)
        {
            cout << "Connect To Named Pipe failed err:" << GetLastError() << endl;
        }
    }
    
#elif _OS_MAC_X_ 
    
    if(err == 0)
    {
        connected = true;
    }
    
#endif
        
    return connected;
}

void cIPCIntf::disConnectIf(void)
{
    
#if _OS_WINDOWS_
    
    /* Open as server */
    if(mode == CIPCINTF_OPEN_MODE_SERVER)
    { 
        /* Disconnect the named pipe from the client */
        DisconnectNamedPipe(hPipe);
    }
    
#endif
    
}

void cIPCIntf::closeIf(bool final)
{
    
#if _OS_WINDOWS_
    
  /* Disconnect & Close */
  DisconnectNamedPipe(hPipe);
  CloseHandle(hPipe);
  
#elif _OS_MAC_X_
  
  if(final == true)
  {
    close(hIpFile);
    close(hOpFile);

    if(mode == CIPCINTF_OPEN_MODE_SERVER)
    {
      /* remove the FIFO */
      unlink(ipFilePath.c_str());
      unlink(opFilePath.c_str());
    }
    
    ifState = false;
  } 
  
#endif
  
}

bool cIPCIntf::getMsg(ipcMsg* pIPCMsg)
{
  bool msgAvai = false;
    
#if _OS_WINDOWS_
  
  DWORD retSize = 0;
  msgAvai = ReadFile(hPipe, pIPCMsg, sizeof(ipcMsg), &retSize, NULL);
  err = GetLastError();
  
#elif _OS_MAC_X_
  
  unsigned int retSize = 0;
  retSize = read(hIpFile, pIPCMsg, sizeof(ipcMsg));
  msgAvai = ((retSize >= sizeof(ipcMsg))?(true):(false));
  err = ((msgAvai == true)?(0):(((errno == 0)?(-1):(errno))));

#endif
  
  //cout << "getMsg " << msgAvai << ", " << retSize << "/" << sizeof(ipcMsg) << ", " << err << endl;
  
  return msgAvai;
}

void cIPCIntf::sendMsg(ipcMsg* pIPCMsg)
{
    bool msgSent = false;
    
#if _OS_WINDOWS_
  
  DWORD sentSize = 0;
  msgSent = WriteFile(hPipe, pIPCMsg, sizeof(ipcMsg), &sentSize, NULL);
  err = GetLastError();
  
#elif _OS_MAC_X_
  
  unsigned int sentSize = 0;
  sentSize = write(hOpFile, pIPCMsg, sizeof(ipcMsg));
  msgSent  = ((sentSize >= sizeof(ipcMsg))?(true):(false));
  err = ((msgSent == true)?(0):(((errno == 0)?(-1):(errno))));
  
#endif
  
  //cout << "sendMsg " << msgSent << ", " << sentSize << "/" << sizeof(ipcMsg) << ", " << err << endl;
}
