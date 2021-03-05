.. _transparent-proxy:

Transparent Proxying
********************

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

.. toctree::
   :maxdepth: 2

   transparent-proxy/build.en
   transparent-proxy/bridge.en
   transparent-proxy/router-inline.en
   transparent-proxy/wccp-configuration.en
   transparent-proxy/wccp-service-config.en

Transparent Proxying is the ability of a proxy (such as ATS) to
intercept connections between clients and servers without being visible.

The general network structure that will be used in this documentation is
shown in the following figure.

.. figure:: ../../static/images/admin/ats-basic-traffic.png
   :align: center
   :alt: ATS basic traffic flow of Transparent Proxy

   ATS basic traffic flow of Transparent Proxy

There must be a gateway device through which all network traffic passes
from the client to the Internet (or external cloud). The gateway is
responsible for effectively splicing ATS in to selected streams of that
traffic. Each traffic stream is split in two, with ATS terminating
both sides. That is, stream green-1, red-2, is split in to the green
connection and the red connection. Note that ATS may or may not be on
the gateway system, the redirected traffic can flow over other network
infrastructure.

Because ATS uses two connections, transparency can be set independently
on the client and origin server (Internet / external cloud) side. We
will define what is generally called "transparent proxy" as two aspects,
*inbound transparency* and *outbound transparency*.

Inbound transparency is a proxy that is transparent to connections that
are inbound to the proxy, i.e. a connection initiated by a client which
connects to the proxy (green-1). Similarly, outbound transparency is a
proxy that is transparent to connections that are outbound from the
proxy, i.e. a connection initiated by the proxy to an origin server
(red-2).

In most situations these two types of transparency are combined, but that is
not required. Traffic Server supports transparency independently on the two
sides.


=ron=
. ._transparent-proxy:

透明代理
********************

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

. .toctree::
: maxdepth: 2

透明代理/ build.en
透明代理/ bridge.en
透明代理/ router-inline.en
透明代理/ wccp-configuration.en
透明代理/ wccp-service-config.en

透明代理是代理(如ATS)的能力
在不可见的情况下截获客户机和服务器之间的连接。

本文档中使用的一般网络结构是
如下图所示。

. .图::. . / . . /静态/图片/ admin / ats-basic-traffic.png
对齐:中心
:alt: ATS透明代理基本流量

透明代理的基本流量

必须有一个网关设备，所有的网络流量都要通过它
从客户端到Internet(或外部云)。网关
负责有效地将ATS拼接到选定的数据流中
流量。每个交通流被分成两部分，以ATS为终点
双方。也就是说，绿色-1，红色-2，被分成绿色
连接和红色连接。注意，ATS可能开着，也可能没开着
网关系统，重定向的流量可以在其他网络上流动
基础设施。

因为ATS使用两个连接，所以可以独立设置透明度
在客户端和源服务器(Internet /外部云)端。我们
将所谓的“透明代理”定义为两个方面，
*入站透明度*和出站透明度*。

入站透明性是一种对连接透明的代理
是否入站到代理，即由哪个客户端发起的连接
连接到代理(绿色-1)。类似地，出站透明性是
的出站连接对其透明的代理
代理，即由代理发起的到源服务器的连接
(红2)。

在大多数情况下，这两种类型的透明度是结合在一起的
不是必需的。流量服务器支持两者独立的透明性
两侧。
=ron=


.. important::

    It is critical to note that any transparency requires specialized
    routing and cannot be done solely by configuring ATS. ATS transparency
    also requires support from the Linux kernel and therefore currently only
    works on sufficiently recent Linux kernels that support the following
    features:

    -  TPROXY
    -  POSIX capabilities

    In addition the specialized routing will require using ``iptables`` and
    in some cases ``ebtables``.

Standard build procedures should work for transparency support but if
not consult these :ref:`more detailed instructions <building-ats-for-transparency>`.

Transparency is configured per server port, not globally. This is done
via the configuration values :ts:cv:`proxy.config.http.server_ports`.
In addition, :ts:cv:`proxy.config.reverse_proxy.enabled` must be enabled if the
client side is transparent. That should be fixed in a future patch.

.. XXX has that been fixed?

.. XXX revisit section below

In the first case use the attribute character (replacing the default
'X')

**Attribute** **Transparency Style** **Reverse Proxy**

``=``
    Full transparency: either

``>``
    Inbound (client) transparency: enabled

``<``
    Outbound (origin server) transparency: either

In the outbound transparent case clients must connect directly to ATS
either through an explicit proxy mechanism or by advertising the IP
address of the ATS server via DNS as the origin server address.

Some tested scenarios --

-  :doc:`transparent-proxy/bridge.en`
-  :doc:`transparent-proxy/router-inline.en`
-  :doc:`transparent-proxy/wccp-configuration.en`


=ron=
. .重要的是::

关键是要注意，任何透明度都需要专门化
路由，不能仅通过配置ATS来完成。ATS的透明度
还需要Linux内核的支持，因此目前只需要
在支持以下内容的最新Linux内核上工作
特点:

——TPROXY
——POSIX能力

此外，特殊的路由将需要使用' ' iptables ' '和
在某些情况下是' ebtables '。

标准的构建过程应该为透明度支持工作，但如果
不要参考这些:参考:'更详细的说明<building-ats-for-transparency> '。</building-ats-for-transparency>

透明度是每个服务器端口配置的，而不是全局配置的。这样做是
通过配置值:ts:cv:`proxy.config.http.server_ports`。
此外,ts:简历:“proxy.config.reverse_proxy。'必须启用，如果
客户端是透明的。这应该会在未来的补丁中修复。

. .这个问题解决了吗?

. .XXX回访部分如下

在第一种情况下使用属性字符(替换默认值)
“X”)

**属性** **透明样式** **反向代理**

' ' = ' '
完全透明:要么

' ' > ' '
入站(客户端)透明性:已启用

' ' < ' '
出站(源服务器)透明度:两者皆有

在出站透明情况下，客户端必须直接连接到ATS
或者通过显式代理机制，或者通过发布IP
ATS服务器地址(通过DNS)作为源服务器地址。

一些测试的场景——

-:医生:“透明代理/ bridge.en”
-:医生:“透明代理/ router-inline.en”
-:医生:“透明代理/ wccp-configuration.en”
=ron=

