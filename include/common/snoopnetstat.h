// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_NET_STAT_H__
#define __SNOOP_NET_STAT_H__

#include <SnoopTypeKey>

// ----------------------------------------------------------------------------
// SnoopNetStat
// ----------------------------------------------------------------------------
class SnoopNetStat
{
protected: // singleton
  SnoopNetStat();
  virtual ~SnoopNetStat();

public:
  static const quint32 UNKNOWN_PROCESS_ID   = 0;
  static const QString UNKNOWN_PROCESS_NAME; // = "";

public:
  virtual quint32 getPID(SnoopTupleFlowKey& infoKey) = 0;
  virtual QString getProcessName(quint32 pid) = 0;

public:
  static SnoopNetStat& instance();
};

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <Iphlpapi.h>
#include <TlHelp32.h>

#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_LONGHORN)
#  include <Iphlpapi.h>
/* Windows Vista Higher                 */
#else

#endif

typedef struct _MIB_TCPROW_EX
{
    DWORD dwState;
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwRemoteAddr;
    DWORD dwRemotePort;
    DWORD dwProcessId;
} MIB_TCPROW_EX, *PMIB_TCPROW_EX;

typedef struct _MIB_TCPTABLE_EX
{
    DWORD dwNumEntries;
    MIB_TCPROW_EX table[ANY_SIZE];
} MIB_TCPTABLE_EX, *PMIB_TCPTABLE_EX;

typedef struct _MIB_TCP6ROW_EX {
    UCHAR ucLocalAddr[16];
    DWORD dwLocalScopeId;
    DWORD dwLocalPort;
    UCHAR ucRemoteAddr[16];
    DWORD dwRemoteScopeId;
    DWORD dwRemotePort;
    DWORD dwState;
    DWORD dwProcessId;
} MIB_TCP6ROW_EX, *PMIB_TCP6ROW_EX;

typedef struct _MIB_TCP6TABLE_EX {
    DWORD dwNumEntries;
    MIB_TCP6ROW_EX table[ANY_SIZE];
} MIB_TCP6TABLE_EX, *PMIB_TCP6TABLE_EX;

typedef struct _MIB_UDPROW_EX
{
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwProcessId;
} MIB_UDPROW_EX, *PMIB_UDPROW_EX;

typedef struct _MIB_UDPTABLE_EX
{
    DWORD dwNumEntries;
    MIB_UDPROW_EX table[ANY_SIZE];
} MIB_UDPTABLE_EX, *PMIB_UDPTABLE_EX;

typedef struct _MIB_UDP6ROW_EX {
    UCHAR ucLocalAddr[16];
    DWORD dwLocalScopeId;
    DWORD dwLocalPort;
    DWORD dwProcessId;
} MIB_UDP6ROW_EX, *PMIB_UDP6ROW_EX;

typedef struct _MIB_UDP6TABLE_EX {
    DWORD dwNumEntries;
    MIB_UDP6ROW_EX table[ANY_SIZE];
} MIB_UDP6TABLE_EX,  *PMIB_UDP6TABLE_EX;

typedef DWORD (WINAPI *GetExtendedTcpTable_t)(PVOID pTcpTable, PDWORD pdwSize, BOOL bOrder, ULONG ulAf, TCP_TABLE_CLASS TableClass, ULONG Reserved);
typedef DWORD (WINAPI *GetExtendedUdpTable_t)(PVOID pUdpTable, PDWORD pdwSize, BOOL bOrder, ULONG ulAf, UDP_TABLE_CLASS TableClass, ULONG Reserved);
typedef DWORD (WINAPI *AllocateAndGetTcpExTableFromStack_t)(PVOID *ppTcpTable, BOOL bOrder, HANDLE hHeap, DWORD dwFlags, DWORD dwFamily);
typedef DWORD (WINAPI *AllocateAndGetUdpExTableFromStack_t)(PVOID *ppUDPTable, BOOL bOrder, HANDLE hHeap, DWORD dwFlags, DWORD dwFamily);

// ----------------------------------------------------------------------------
// SnoopNetStatWin
// ----------------------------------------------------------------------------
class SnoopNetStatWin : public SnoopNetStat, public VLockable
{
  friend class SnoopNetStat;
protected:
  //
  // for getPID
  //
  DWORD                   dwTcpSize;
  DWORD                   dwUdpSize;
  MIB_TCPTABLE_OWNER_PID* pTcp;
  MIB_UDPTABLE_OWNER_PID* pUdp;
  GetExtendedTcpTable_t   GetExtendedTcpTable;
  GetExtendedUdpTable_t   GetExtendedUdpTable;
  HMODULE                 hDLL;

private: // singleton
  SnoopNetStatWin();
  virtual ~SnoopNetStatWin();

protected:
  QList<Ip> myIpList;

public:
  virtual quint32 getPID(SnoopTupleFlowKey& infoKey);
  virtual QString getProcessName(quint32 pid);
};
#endif // WIN32

#ifdef linux
// ----------------------------------------------------------------------------
// SnoopNetStatLinux
// ----------------------------------------------------------------------------
class SnoopNetStatLinux : public SnoopNetStat
{
public:
  virtual quint32 getPID(SnoopTupleFlowKey& infoKey);
  virtual QString getProcessName(quint32 pid);
};
#endif // linux

#endif // __SNOOP_NET_STAT_H__
