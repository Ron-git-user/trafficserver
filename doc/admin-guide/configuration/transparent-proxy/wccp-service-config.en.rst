.. Licensed to the Apache Software Foundation (ASF) under one
   or more contributor license agreements.  See the NOTICE file
   distributed with this work for additional information
   regarding copyright ownership.  The ASF licenses this file
   to you under the Apache License, Version 2.0 (the
   "License"); you may not use this file except in compliance
   with the License.  You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing,
   software distributed under the License is distributed on an
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
   KIND, either express or implied.  See the License for the
   specific language governing permissions and limitations
   under the License.

.. include:: ../../../common.defs

.. _admin-wccp-service-config:

WCCP Service Configuration
**************************

The service definition file is used by :program:`traffic_wccp` and
:program:`traffic_server` directly.

The elements in the security definition file are inspired by the
`WCCP RFC (8/2012) <http://tools.ietf.org/html/draft-mclaggan-wccp-v2rev1-00>`_.
There is also an older version of the RFC that shows up commonly in search results,
`WCCP (4/2001) <https://tools.ietf.org/id/draft-wilson-wrec-wccp-v2-01.txt>`_,
and was the RFC reference used in the original WCCP support for |TS| several
years ago.

A sample service group file is included in the source tree under
:program:`traffic_wccp`.

Security Section
================

In the security section, you can define a password shared between the WCCP Client and the WCCP router.  This password is used to encrypt the WCCP traffic.  It is optional, but highly recommended.

Attributes in this section

*  option  - Must be set to MD5 if you want to encrypt your WCCP traffic

*  key – The same password that you set with the associated WCCP router.

=ron=
. .授权给Apache软件基金会(ASF)
或更多的贡献者许可协议。查看通知文件
与此工作一起发布的附加信息
关于版权的所有权。ASF对该文件进行license
在Apache许可下，版本2.0 (the
“许可”);除非符合要求，否则不能使用该文件
的许可证。你可以在以下网站获得一份许可证副本

http://www.apache.org/licenses/LICENSE-2.0

除非适用法律要求或书面同意，
在许可证下发布的软件是通过
以“现状”为基础，不含任何保证或条件
善良，不管是明示的还是暗示的。查看许可证
特定的语言管理权限和限制
根据许可证。

. .包括 :: ../../../ common.defs

. ._admin-wccp-service-config:

WCCP服务配置
**************************

服务定义文件用于:program: ' traffic_wccp '和
直接:计划:“traffic_server”。

安全性定义文件中的元素受到
' WCCP RFC (8/2012) <http: tools.ietf.org="" html="" draft-mclaggan-wccp-v2rev1-00=""> ' _。</http:>
还有一个老版本的RFC，经常出现在搜索结果中，
WCCP (4/2001) < https://tools.ietf.org/id/draft -威尔逊wrec WCCP - v2 - 01. - txt >”_,
而RFC在WCCP中所使用的原始参考则支持|TS|若干
年前的事了。

下面的源树中包含一个示例服务组文件
项目:“traffic_wccp”。

安全部分
================

在security部分中，您可以定义在WCCP客户机和WCCP路由器之间共享的密码。此密码用于加密WCCP通信。它是可选的，但强烈推荐使用。

本节中的属性

*选项-必须设置为MD5，如果你想加密你的WCCP流量

*密钥-与你设置的WCCP路由器相同的密码。
=ron=

Services Section
================

In the services section you can define a list of service groups.  Each top level entry is a separate service group.

Service group attributes include

*  name – A name for the service.  Not used in the rest of the WCCP processing.

*  description – A description of the service.  Again, not used in the rest of the WCCP processing.

*  id - The security group ID.  It must match the service group ID that has been defined on the associated WCCP router.  This is the true service group identifier from the WCCP perspective.

* type – This defines the type of service group either "STANDARD" or "DYNAMIC".  There is one standard defined service group, HTTP with the id of 0.  The 4/2001 RFC indicates that id's 0-50 are reserved for well known service groups.  But more recent 8/2012 RFC indicates that values 0 through 254 are valid service id's for dynamic services.  To avoid differences with older WCCP routers, you probably want to avoid dynamic service ID's 0 through 50.

* priority – This is a value from 0 to 255.  The higher number is a higher priority.  Well known (STANDARD) services are set to a value of 240.  If there are multiple service groups that could match a given packet, the higher priority service group is applied. RFC  For example, you have service group 100 defined for packets with destination port 80, and service group 101 defined for packets with source port 1024.  For a packet with destination port set to 80 and source port set to 1024, the priorities of the service groups would need to be compared to determine which service group applies.

* protocol – This is IP protocol number that should match.  Generally this is set to 6 (TCP) or 17 (UDP).

* assignment – WCCP supports multiple WCCP clients supporting a single service group.  However, the current WCCP client implementation in Traffic Server assumes there is only a single WCCP client, and so creates assignment tables that will direct all traffic to that WCCP client.  The assignment type is either hash or mask, and if it is not set, it defaults to hash.  If Traffic Server ever supports more than one cache, it will likely only support a balanced hash assignment.  The mask/value assignment seems to be better suited to situations where the traffic needs to be more strongly controlled.

* primary-hash – This is the element of the packet that is used to compute the primary key.  The value options are src_ip, dst_ip, src_port, or  dst_port. This entry is a list, so multiple values can be specified.  In that case, all the specified packet attributes will be used to compute the hash bucket.  In the current implementation, the primary hash value does not matter, since the client always generates a hash table that directs all matching traffic to it.  But if multiple clients are ever supported, knowledge of the local traffic distribution could be used to pick a packet attribute that will better spread traffic over the WCCP clients.
*  alt-hash – The protocol supports a two level hash.  This attribute is a list with the same value options as for primary-hash.  Again, since the current Traffic Server implementation only creates assignment tables to a single client, specifying the alt-hash values does nothing.

* ports – This is a list of port values.  Up to 8 port values may be included in a service group definition.

* port-type – This attribute can have the value of src or dst.  If not specified, it defaults to dst.  It indicates whether the port values should be interpreted as source ports or destination ports.

* forward – This is a list.  The list of the values can be GRE or L2.  This advertises how the client wants to process WCCP packets.  GRE means that the packets will be delivered in a GRE tunnel.  This is the default.  L2 means that the client is on the same network and can get traffic delivered to it from the router by L2 routing (MAC addresses).

* return – The WCCP protocol allows a WCCP client to decline a packet and return it back to the router.  The current WCCP client implementation never does this.  The value options are the same as for the forward attribute.

* routers – This is the list of router addresses the WCCP client communicates with.  The WCCP protocols allows for multiple WCCP routers to be involved in a service group.  The multiple router scenario has at most been lightly tested in the Traffic Server implementation.

* proc-name – This attribute is only used by traffic_wccp.  It is not used in the traffic_server WCCP support.  This is the path to a process' PID file.  The service group is advertised to the WCCP router if the process identified in the PID file is currently operational.

=ron=
服务部分
================

在services部分中，您可以定义一个服务组列表。每个顶级入口都是一个单独的服务组。

服务组属性包括

* name -服务的名称。在WCCP处理的其余部分中不使用。

*描述-对服务的描述。同样，没有在WCCP处理的其余部分中使用。

* id -安全组id。必须与在关联的WCCP路由器上定义的服务组id匹配。从WCCP的角度来看，这是真正的服务组标识符。

*类型-定义服务组的类型为“标准”或“动态”。有一个标准定义的服务组，id为0的HTTP。4/2001 RFC表示id的0-50保留给知名的服务组。但是最近的8/2012 RFC指出0到254是动态服务的有效服务id。为了避免与旧的WCCP路由器的不同，您可能希望避免动态服务ID的0到50。

* priority -取值范围是0到255。数字越大，优先级越高。众所周知的(标准的)服务被设置为240。如果有多个服务组可以匹配同一个报文，则优先级高的服务组应用。RFC例如，对于目的端口为80的报文定义了服务组100，对于源端口为1024的报文定义了服务组101。对于目标端口设置为80、源端口设置为1024的数据包，需要比较服务组的优先级，以确定应用哪个服务组。

* protocol -这是应该匹配的IP协议号。通常设置为6 (TCP)或17 (UDP)。

*分配- WCCP支持多个WCCP客户端支持单个服务组。然而，流量服务器中当前的WCCP客户端实现假定只有一个WCCP客户端，因此创建了将所有流量指向该WCCP客户端的分配表。赋值类型为散列或掩码，如果未设置，则默认为散列。如果流量服务器支持多个缓存，它可能只支持平衡哈希分配。掩码/值分配似乎更适合需要更严格控制流量的情况。

* primary-hash -这是数据包中用来计算主键的元素。取值包括:src_ip、dst_ip、src_port、dst_port。这个条目是一个列表，因此可以指定多个值。在这种情况下，将使用所有指定的包属性来计算散列桶。在当前的实现中，主哈希值并不重要，因为客户端总是生成一个哈希表，将所有匹配的流量指向它。但是，如果曾经支持多个客户机，可以使用本地流量分布的知识来选择一个包属性，以便更好地在WCCP客户机上传播流量。
* alt-hash -协议支持两级hash。该属性是一个列表，与primary-hash具有相同的值选项。同样，由于当前的流量服务器实现仅为单个客户机创建分配表，因此指定alt-hash值没有任何作用。

*端口-这是一个端口值列表。一个服务组定义中最多可以包含8个端口值。

* port-type—该属性的值可以是src或dst。如果未指定，则默认为夏令时。它指示端口值应该被解释为源端口还是目标端口。

* forward -这是一个列表。取值包括GRE和L2。这将告知客户端希望如何处理WCCP数据包。GRE表示报文将在GRE隧道中发送。这是默认值。L2意味着客户端在同一网络上，可以通过L2路由(MAC地址)从路由器获得传送到它的流量。

* return - WCCP协议允许WCCP客户端拒绝一个数据包并将其返回给路由器。当前的WCCP客户端实现从来不会这样做。值选项与forward属性相同。

*路由器-这是与WCCP客户端通信的路由器地址列表。WCCP协议允许多个WCCP路由器参与到一个服务组中。在流量服务器实现中对多路由器场景进行了简单的测试。

* proc-name -该属性仅被traffic_wccp使用。在traffic_server WCCP支持中不使用。这是一个进程PID文件的路径。如果PID文件中标识的进程当前是可操作的，那么服务组就会发布到WCCP路由器。
=ron=
