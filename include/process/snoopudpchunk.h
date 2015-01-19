// ----------------------------------------------------------------------------
//
// Snoop Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __SNOOP_UDP_CHUNK_H__
#define __SNOOP_UDP_CHUNK_H__

#include <VCommon>

// ----------------------------------------------------------------------------
// SnoopUdpChunkInfo
// ----------------------------------------------------------------------------
class SnoopUdpChunkInfo
{
public:
  static const int DSCR_SIZE = 4;
  static const int INFO_SIZE = 8;

public:
  QByteArray dscr; // 4 uint8_t
  quint16    id;   // 2 uint8_t
  quint16    len;  // 2 uint8_t
};

// ----------------------------------------------------------------------------
// SnoopUdpChunkPayload
// ----------------------------------------------------------------------------
class SnoopUdpChunkPayload
{
public:
  QByteArray header;
  QByteArray body;
};

// ----------------------------------------------------------------------------
// SnoopUdpChunk
// ----------------------------------------------------------------------------
class SnoopUdpChunk
{
public:
  SnoopUdpChunkInfo    info;
  SnoopUdpChunkPayload payload;

public:
  int encode(QByteArray& ba); // into ba
  int decode(int headerSize, QByteArray& ba); // from ba
};

// ----------------------------------------------------------------------------
// SnoopUdpChunks
// ----------------------------------------------------------------------------
typedef QList<SnoopUdpChunk> SnoopUdpChunks;

#endif // __SNOOP_UDP_CHUNK_H__
