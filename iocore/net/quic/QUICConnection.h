/** @file
 *
 *  A brief file description
 *
 *  @section license License
 *
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include "QUICPacketTransmitter.h"
#include "QUICFrameTransmitter.h"
#include "QUICFrameHandler.h"
#include "QUICTransportParameters.h"

class QUICApplication;
class QUICStreamManager;
class SSLNextProtocolSet;

class QUICConnection : public QUICPacketTransmitter, public QUICFrameTransmitter, public QUICFrameHandler
{
public:
  /*
   * Retruns the maximum packet size at the time called
   *
   * The size depends on PMTU.
   */
  virtual uint32_t maximum_quic_packet_size() = 0;

  /*
   * Returns the mimimum packet size at the time called
   *
   * If the connection is an outgoing connection and you have not sent Client Initial packet,
   * this return the minimum size for it, which is 1200.
   */
  virtual uint32_t minimum_quic_packet_size() = 0;

  virtual QUICStreamManager *stream_manager() = 0;

  virtual uint32_t pmtu()                                   = 0;
  virtual NetVConnectionContext_t direction()               = 0;
  virtual SSLNextProtocolSet *next_protocol_set()           = 0;
  virtual void close(QUICError error)                       = 0;
  virtual QUICPacketNumber largest_received_packet_number() = 0;
  virtual QUICPacketNumber largest_acked_packet_number()    = 0;
};
