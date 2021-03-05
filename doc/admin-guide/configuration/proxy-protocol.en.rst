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

.. include:: ../../common.defs

.. _proxy-protocol:

Proxy Protocol
****************

The `PROXY protocol <https://www.haproxy.com/blog/haproxy/proxy-protocol/>`_
provides a means of passing connection information between layers of the proxy
infrastructure.  Without the PROXY protocol, |TS| would only have connection
information from the previous hop connecting to |TS| and not the actual
originating client connection information.  This can be done over either HTTP or
TLS connections.

.. note::

    The current implementation doesn't support TLV fields of Version 2.

The Proxy Protocol must be enabled on each port.  See
:ts:cv:`proxy.config.http.server_ports` for information on how to enable the
Proxy Protocol on a port.  Once enabled, all incoming requests must be prefaced
with the PROXY v1/v2 header.  Any request not preface by this header will be
dropped.

As a security measure, an optional list of trusted IP addresses may be
configured with :ts:cv:`proxy.config.http.proxy_protocol_allowlist`.

   .. important::

       If the allowlist is configured, requests will only be accepted from these
       IP addresses and must be prefaced with the PROXY v1/v2 header.

1. HTTP Forwarded Header

The client IP address in the PROXY protocol header is passed to the origin server via an HTTP `Forwarded:
<https://tools.ietf.org/html/rfc7239>`_ header. See :ts:cv:`proxy.config.http.insert_forwarded` for configuration information.
Detection of the PROXY protocol header is automatic.  If the PROXY header
precludes the request, it will automatically be parse and made available to the
Forwarded: request header sent to the origin server.

2. Outbound PROXY protocol

See :ts:cv:`proxy.config.http.proxy_protocol_out` for configuration information.

Example
-------

As an example, consider the following topology:

.. figure:: ../../static/images/admin/proxy-protocol.png
   :align: center
   :alt: PROXY protocol transformed into a Forwarded: header

   PROXY protocol header flow

Without the PROXY protocol header, the client IP would only be reported
accurately to the Load Balancer.  |TS| would only see the connection from the
Load Balancer.  Similarly, the Web Server would only see the connection from
|TS|.  In the example above, if the client initiated a TLS connection, the Web
Server would see the connection originating from |TS| at ``10.0.0.2``:

.. code-block:: lua

    Forwarded: for=10.0.0.2;by=10.0.0.1;proto=https;host=test000001.com

If the Load Balancer has the Proxy Protocol enabled, requests sent through the
Load Balancer will be preceded with the PROXY header.  |TS| will detect the
PROXY header and transform that into the Forwarded: HTTP header if configured to
insert the Forwarded: header with the ``for`` parameter.  In the example above,
if the client initiated a TLS connection, the Web Server can use the Forwarded:
header to determine the TLS connection originated from the client at ``192.168.1.100``:

.. code-block:: lua

    Forwarded: for=192.168.2.100;by=10.0.0.2;proto=https;host=test000001.com


References
==========

-  `The PROXY protocol Versions 1 & 2
   <https://www.haproxy.org/download/1.8/doc/proxy-protocol.txt>`_

-  `Forwarded HTTP Extension
   <https://tools.ietf.org/html/rfc7239#page-6>`_


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

. .包括::. . / . . / common.defs

. ._proxy-protocol:

代理协议
****************

'代理协议<https: www.haproxy.com="" blog="" haproxy="" proxy-protocol=""></https:> ' _
提供在代理层之间传递连接信息的方法
基础设施。如果没有代理协议，|TS|将只有连接
信息来自前一跳连接到|TS|而不是实际的|
初始客户端连接信息。这可以通过HTTP或
TLS连接。

. .注意::

当前的实现不支持版本2的TLV字段。

代理协议必须在每个端口上启用。看到
ts:简历:“proxy.config.http。查看如何启用。server_ports的信息
端口上的代理协议。一旦启用，所有传入请求都必须有前缀
使用代理v1/v2报头。任何不以此标题开头的请求将被
下降了。

作为一种安全措施，可选的可信IP地址列表
配置:ts:简历:“proxy.config.http.proxy_protocol_allowlist”。

. .重要的是::

如果配置了allowlist，则只接受来自这些对象的请求
IP地址，并且必须在前面加上代理v1/v2头。

1. HTTP转发头

代理协议头中的客户端IP地址通过HTTP ' Forwarded:
< https://tools.ietf.org/html/rfc7239 > ' _标题。看到:ts:简历:“proxy.config.http。获取配置信息insert_forwarded`。
自动检测代理协议报头。如果代理头
排除了请求，它将被自动解析并对
转发:发送到源服务器的请求头。

2. 海外代理协议

看到:ts:简历:“proxy.config.http。proxy_protocol_out的配置信息。

例子
-------

以下面的拓扑为例:

. .图::. . / . . /静态/图片/ admin / proxy-protocol.png
对齐:中心
:alt:代理协议转换为转发:头

代理协议报头流

如果没有代理协议头，则只会报告客户端IP
准确到负载均衡器。|TS|只会看到来自
负载均衡器。类似地，Web服务器只能看到来自的连接
| TS |。在上面的示例中，如果客户端发起TLS连接，则Web
服务器会在“10.0.0.2”处看到来自|TS|的连接:

. .代码块:lua

转发:= 10.0.0.2;通过= 10.0.0.1;表示原型= https;主机= test000001.com

如果负载均衡器启用了代理协议，则通过
负载均衡器的前面会有代理头。|TS|将检测到
代理报头，并将其转换为转发:HTTP报头，如果配置为
插入带有' ' for ' '参数的Forwarded:头文件。在上面的例子中，
如果客户端发起TLS连接，Web服务器可以使用转发的:
报头来确定来自客户端192.168.1.100的TLS连接:

. .代码块:lua

转发:= 192.168.2.100;通过= 10.0.0.2;原型= https;主机= test000001.com


参考文献
==========

-“代理协议版本1和2
< https://www.haproxy.org/download/1.8/doc/proxy-protocol.txt > _

转发的HTTP扩展名
< https://tools.ietf.org/html/rfc7239第6页> _
=ron=

