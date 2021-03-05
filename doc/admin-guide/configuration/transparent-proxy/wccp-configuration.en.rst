WCCP Configuration
******************

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

.. _wccp-configuration:

.. toctree::
   :maxdepth: 2

`WCCP <http://cio.cisco.com/en/US/docs/ios/12_0t/12_0t3/feature/guide/wccp.html>`_
is de-facto semi-standard used by routers to redirect network traffic to
caches. It is available on most Cisco™ routers although it does not
appear to be officially supported by Cisco. The primary benefits of WCCP
are

-  If already have a router that supports WCCP inline you do not
   have to change your network topology.
-  WCCP fails open so that if the Traffic Server machine fails, it is
   bypassed and users continue to have Internet access.

Use of WCCP only makes sense for client side transparency [1]_
because if the clients are explicitly proxied by Traffic Server there's
no benefit to WCCP fail open, as the clients will continue to directly
access the unresponsive Traffic Server host. It would be better to
adjust the routing tables on the router for explicit proxying.

Because the router serves as the inline network element, Traffic Server
must run on a separate host. This host can be located anywhere as long
as Traffic Server is either on the same network segment or a GRE tunnel
can be maintained between the Traffic Server host and the router.

|important| This document presumes that the router is already properly
configured to handle traffic between the clients and the origin servers.
If you are not certain, verify it before attempting to configure Traffic
Server with WCCP. This is also a good state to which to revert should
the configuration go badly.

Configuration overview
======================

Setting WCCP is a three step process, first configuring the router, the
Traffic Server host, and Traffic Server.

|image1| The router will **not** respond to WCCP protocol packets unless
explicitly configured to do so. Via WCCP, the router can be made to
perform packet interception and redirection needed by Traffic Server
transparency. The WCCP protocol in effect acts as means of controlling a
rough form of policy routing with positive heartbeat cutoff.

The Traffic Server host system must also be configured using
``iptables`` to accept connections on foreign addresses. This is done
roughly the same way as the standard transparency use.

Finally Traffic Server itself must be configured for transparency and
use of WCCP. The former is again very similar to the standard use, while
WCCP configuration is specific to WCCP and uses a separate configuration
file, referred to by the :file:`records.config` file.

The primary concern for configuration in which of three basic topologies
are to be used.

-  Dedicated -- Traffic Server traffic goes over an interface that is
   not used for client nor origin server traffic.
-  Shared -- Traffic Server traffic shares an interface with client or
   server traffic.
-  Inside Shared -- Traffic Server and client traffic share an
   interface.
-  Outside Shared -- Traffic Server and
   origin server traffic share an interface.

In general the dedicated topology is preferred. However, if the router
has only two interfaces one of the shared topologies will be
required [2]_ Click the links above for more detailed configuration
information on a specific topology.


=ron=
WCCP配置
******************

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

. ._wccp-configuration:

. .toctree::
: maxdepth: 2

“WCCP < http://cio.cisco.com/en/US/docs/ios/12_0t/12_0t3/feature/guide/wccp.html > _
事实上是半标准使用路由器重定向网络流量到
缓存。它在大多数Cisco™路由器上是可用的，尽管它不是
似乎得到了思科的官方支持。WCCP的主要好处
是

-如果已经有一个路由器，支持WCCP内联你不
必须更改您的网络拓扑。
—WCCP打开失败，如果流量服务器机器发生故障，则是WCCP
被绕过的用户可以继续上网。

使用WCCP只对客户端透明[1]_有意义
因为如果客户端被流量服务器显式代理
打开WCCP没有任何好处，因为客户端会直接继续
访问没有响应的流量服务器主机。最好是
为显式代理调整路由器上的路由表。

因为路由器充当内联网络元素，流量服务器
必须在单独的主机上运行。这个主机可以位于任何地方
as流量服务器属于同一网段或者属于GRE隧道
可以在流量服务器主机和路由器之间进行维护。

|重要|本文档假定路由器已经正常
配置为处理客户机和源服务器之间的通信。
如果不确定，请在配置流量之前验证
WCCP服务器。这也是一个应该恢复的良好状态
配置出现问题。

配置概述
======================

设置WCCP有三个步骤，首先是配置路由器，然后是
流量服务器主机，流量服务器。

路由器不会响应WCCP协议包，除非
显式配置为这样做。通过WCCP，路由器可以做到
执行流量服务器需要的数据包拦截和重定向
透明度。WCCP协议实际上是控制a
带有正心跳切断的策略路由的粗略形式。

流量服务器主机系统也必须使用
接受外部地址的连接。这样做是
与标准透明度使用的方式大致相同。

最后，流量服务器本身必须配置为透明和
WCCP的使用。前者同样非常类似于标准用法，而
WCCP配置是特定于WCCP的，并且使用一个单独的配置
文件，由:file: ' records引用。配置文件。

在三种基本拓扑中配置的主要关注点
都将被使用。

- Dedicated——Traffic服务器的流量通过接口
不用于客户端或源服务器通信。
- Shared——Traffic服务器流量与client或共享接口
服务器流量。
- Inside Shared——流量服务器和客户端流量共享一个
接口。
-外部共享——流量服务器和
源服务器的流量共享一个接口。

一般来说，首选专用拓扑。但是，如果路由器
共享拓扑中只有一个是两个接口吗
需要[2]_点击上面的链接了解更多详细的配置
关于特定拓扑的信息。
=ron=


Shared interface issues
-----------------------

A shared interface topology has additional issues compared to a
dedicated topology that must be handled. Such a topology is required if
the router has only two interfaces, and because of these additional
issues it is normally only used in such cases, although nothing prevents
it use even if the router has three or more interfaces.

The basic concept for a shared interface is to use a tunnel to simulate
the dedicated interface case. This enables the packets to be
distinguished at layer 3. For this reason, layer 2 redirection cannot be
used because the WCCP configuration cannot distinguish between packets
returning from the origin server and packets returning from Traffic
Server as they are distinguished only by layer 2 addressing [3]_.
Fortunately the GRE tunnel used for packet forwarding and return can be
used as the simulated interface for Traffic Server.

Frequently encountered problems
-------------------------------

MTU and fragmentation
~~~~~~~~~~~~~~~~~~~~~

In most cases the basic configuration using a tunnel in any topology can
fail due to issues with fragmentation. The socket logic is unable to
know that its packets will eventually be put in to a tunnel which will
by its nature have a smaller
`MTU <http://en.wikipedia.org/wiki/Maximum_transmission_unit>`_ than the
physical interface which it uses. This can lead to pathological behavior
or outright failure as the packets sent are just a little too big. It is
not possible to solve easily by changing the MTU on the physical
interface because the tunnel interface uses that to compute its own MTU.

References
==========

-  `WCCP Router Configuration Commands - IOS
   12.2 <http://www.cisco.com/en/US/docs/ios/12_2/configfun/command/reference/frf018.html>`_








.. [1]
   Server side transparency should also be used, but it is not as
   significant. In its absence, however, origin servers may see the
   source address of connections suddenly change from the Traffic Server
   address to client addresses, which could cause problems. Further, the
   primary reason for not having server side transparency is to hide
   client addresses which is defeated if the Traffic Server host fails.

.. [2]
   If your router has only one interface, it's hardly a *router*.

.. [3]
   This is not fundamentally impossible, as the packets are distinct in
   layer

.. |important| image:: ../../../static/images/docbook/important.png
.. |image1| image:: ../../../static/images/docbook/important.png


=ron=
共享接口问题
-----------------------

与共享接口拓扑相比，共享接口拓扑有额外的问题
必须处理的专用拓扑。如果需要这样的拓扑
路由器只有两个接口，由于这些额外的
它通常只在这种情况下使用，尽管没有防止
它使用即使路由器有三个或更多的接口。

共享接口的基本概念是使用隧道进行模拟
专用接口案例。这使得数据包可以
在第3层区分。因此，第2层重定向不能
使用，因为WCCP配置不能区分数据包
从源服务器返回和数据包从流量返回
服务器，因为他们只有第二层地址[3]_区分。
幸好GRE隧道可以用于报文的转发和返回
用作流量服务器的模拟接口。

经常遇到问题
-------------------------------

MTU和碎片
~~~~~~~~~~~~~~~~~~~~~

在大多数情况下，在任何拓扑中使用隧道的基本配置都可以
由于碎片问题而失败。套接字逻辑无法
知道它的包最终会被放入隧道中
就其本质而言有一个较小的
' MTU <http: en.wikipedia.org="" wiki="" maximum_transmission_unit=""> ' _小于</http:>
它使用的物理接口。这可能会导致病理行为
或者完全失败，因为发送的数据包有点太大了。它是
不可能通过改变物理上的MTU来轻松解决
接口，因为tunnel接口使用该接口计算自己的MTU。

参考文献
==========

WCCP路由器配置命令
12.2 < http://www.cisco.com/en/US/docs/ios/12_2/configfun/command/reference/frf018.html > _








. .[1]
服务器端透明性也应该被使用，但它不是
有很重要的意义。然而，如果没有它，源服务器可能会看到
连接源地址突然从流量服务器改变
地址到客户端地址，这可能会导致问题。此外,
服务器端不透明的主要原因是为了隐藏
如果流量服务器主机失败，将失败的客户端地址。

. .[2]
如果你的路由器只有一个接口，那它就不是一个路由器。

. .[3]
这不是根本不可能的，因为包是不同的
层

. .| |重要形象 :: ../../../ 静态/图片/ docbook / important.png
. .| image1 |图片 :: ../../../ 静态/图片/ docbook / important.png
=ron=

