.. _reverse-proxy-and-http-redirects:

Reverse Proxy and HTTP Redirects
********************************

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

Reverse Proxy and HTTP Redirects
================================

As a reverse proxy cache, Traffic Server serves requests on behalf of
origin servers. Traffic Server is configured in such a way that it
appears to clients like a normal origin server.

.. toctree::
   :maxdepth: 2

Understanding Reverse Proxy Caching
===================================

With *forward proxy caching*, Traffic Server handles web requests to origin
servers on behalf of the clients requesting the content. *Reverse proxy
caching* (also known as *server acceleration*) is different because Traffic
Server acts as a proxy cache on behalf of the origin servers that store the
content. Traffic Server is configured to behave outwardly as origin server
which the client is trying to connect to. In a typical scenario the advertised
hostname of the origin server resolves to Traffic Server, which serves client
requests directly, fetching content from the true origin server when necessary.

Reverse Proxy Solutions
-----------------------

There are many ways to use Traffic Server as a reverse proxy. Below are
a few example scenarios.

-  Offload heavily-used origin servers.

-  Deliver content efficiently in geographically distant areas.

-  Provide security for origin servers that contain sensitive information.

Offloading Heavily-Used Origin Servers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Traffic Server can accept requests on behalf of the origin server and improve
the speed and quality of web serving by reducing load and hot spots on
backup origin servers. For example, a web host can maintain a scalable
Traffic Server system with a set of low-cost, low-performance,
less-reliable PC origin servers as backup servers. In fact, a single
Traffic Server can act as the virtual origin server for multiple backup
origin servers, as shown in the figure below.

.. figure:: /static/images/admin/revproxy.jpg
   :align: center
   :alt: Traffic Server as reverse proxy for a pair of origin servers

   Traffic Server as reverse proxy for a pair of origin servers

Delivering Content in Geographically-Dispersed Areas
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Traffic Server can be used in reverse proxy mode to accelerate origin
servers that provide content to areas not located within close
geographical proximity. Caches are typically easier to manage and are
more cost-effective than replicating data. For example, Traffic Server
can be used as a mirror site on the far side of a trans-Atlantic link to
serve users without having to fetch the request and content across
expensive, or higher latency, international connections. Unlike replication,
for which hardware must be configured to replicate all data and to handle peak
capacity, Traffic Server dynamically adjusts to optimally use the
serving and storing capacity of the hardware. Traffic Server is also
designed to keep content fresh automatically, thereby eliminating the
complexity of updating remote origin servers.

Providing Security for an Origin Server
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


=ron=
. ._reverse-proxy-and-http-redirects:

反向代理和HTTP重定向
********************************

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

反向代理和HTTP重定向
================================

作为反向代理缓存，流量服务器代表请求服务
起源服务器。流量服务器的配置方式是
对客户端来说就像一个普通的源服务器。

. .toctree::
: maxdepth: 2

理解反向代理缓存
===================================

使用转发代理缓存*，流量服务器处理web请求的来源
服务器代表请求内容的客户机。*反向代理
缓存*(也称为*服务器加速*)是不同的，因为流量
服务器充当代理缓存，代表存储
内容。流量服务器被配置为在外部表现为源服务器
客户端试图连接到的。在一个典型的场景中，广告
源服务器的主机名解析为通信服务器，它为客户端服务
直接请求，必要时从真正的源服务器获取内容。

反向代理的解决方案
-----------------------

有很多方法可以将流量服务器用作反向代理。下面是
几个示例场景。

—卸载频繁使用的源服务器。

-在地理位置遥远的地区有效地传递内容。

—为包含敏感信息的源服务器提供安全保障。

卸载大量使用的源服务器
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

流量服务器可以代表源服务器接受请求并进行改进
通过减少负载和热点来提高网络服务的速度和质量
备份源服务器。例如，web主机可以保持可伸缩性
一套低成本、低性能的交通服务器系统，
不太可靠的PC源服务器作为备份服务器。事实上，一个人
流量服务器可以作为虚拟源服务器进行多次备份
源服务器，如下图所示。

. .图::/ admin / revproxy.jpg /静态图像
对齐:中心
:alt:流量服务器作为一对源服务器的反向代理

通信服务器作为一对源服务器的反向代理

在地理上分散的区域提供内容
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

流量服务器可以用反向代理方式加速源
向不在附近的区域提供内容的服务器
地理上的接近。缓存通常更容易管理
比复制数据更划算。例如，流量服务器
可以作为镜像站点的远端跨大西洋的链接吗
无需获取请求和内容就能服务于用户
昂贵的国际连接，或更高的延迟。与复制,
必须将硬件配置为复制所有数据并处理peak
容量，流量服务器动态调整，以优化使用
硬件的服务容量和存储容量。流量服务器
旨在保持内容的自动更新，从而消除
更新远程源服务器的复杂性。

为源服务器提供安全性
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
=ron=


Traffic Server can be used in reverse proxy mode to provide security for
an origin server. If an origin server contains sensitive information
that you want to keep secure inside your firewall, then you can use a
Traffic Server outside the firewall as a reverse proxy for that origin
server. When outside clients try to access the origin server, the
requests instead go to Traffic Server. If the desired content is not
sensitive, then it can be served from the cache. If the content is
sensitive and not cacheable, then Traffic Server obtains the content
from the origin server (the firewall allows only Traffic Server access
to the origin server). The sensitive content resides on the origin
server, safely inside the firewall.

How Does Reverse Proxy Work?
----------------------------

When a browser makes a request, it normally sends that request directly
to the origin server. When Traffic Server is in reverse proxy mode, it
intercepts the request before it reaches the origin server. Typically,
this is done by setting up the DNS entry for the origin server (i.e.,
the origin server's advertised hostname) so it resolves to the Traffic
Server IP address. When Traffic Server is configured as the origin
server, the browser connects to Traffic Server rather than the origin
server. For additional information, see `HTTP Reverse Proxy`_.

.. note::

    To avoid a DNS conflict, the origin server's hostname and its advertised
    hostname must not be the same.

HTTP Reverse Proxy
==================

In reverse proxy mode, Traffic Server serves HTTP requests on behalf of
a web server. The figure below illustrates how Traffic Server in reverse
proxy mode serves an HTTP request from a client browser.

.. figure:: /static/images/admin/httprvs.jpg
   :align: center
   :alt: HTTP reverse proxy

   HTTP reverse proxy

The figure above demonstrates the following steps:

.. List below should remain manually numbered, as the entries correspond to numbers in the figure above.

1. A client browser sends an HTTP request addressed to a host called
   ``www.host.com`` on port 80. Traffic Server receives the request
   because it is acting as the origin server (the origin server's
   advertised hostname resolves to Traffic Server).

2. Traffic Server locates a map rule in the :file:`remap.config` file and
   remaps the request to the specified origin server (``realhost.com``).

3. If the request cannot be served from cache, Traffic Server opens a
   connection to the origin server (or more likely, uses an existing
   connection it has pre-established), retrieves the content, and optionally
   caches it for future use.

4. If the request was a cache hit and the content is still fresh in the cache,
   or the content is now available through Traffic Server because of step 3,
   Traffic Server sends the requested object to the client from the cache
   directly.

.. note::

    Traffic Server, when updating its own cache from the origin server, will
    simultaneously deliver that content to the client while updating its
    cache database. The response to the client containing the requested object
    will begin as soon as Traffic Server has received and processed the full
    response headers from the origin server.

To configure HTTP reverse proxy, you must perform the following tasks:

-  Create mapping rules in the :file:`remap.config` file (refer to `Creating
   Mapping Rules for HTTP Requests`_). ::

      map http://www.host.com http://realhost.com

-  Enable the reverse proxy option (refer to `Enabling HTTP Reverse Proxy`_).

In addition to the tasks above, you can also `Setting Optional HTTP Reverse Proxy Options`_.

Handling Origin Server Redirect Responses
-----------------------------------------

=ron=
流量服务器可以采用反向代理方式为其提供安全性
一个源服务器。如果源服务器包含敏感信息
你想要在你的防火墙内保持安全，然后你可以使用
防火墙外的流量服务器作为该源的反向代理
服务器。当外部客户端试图访问源服务器时，
请求将转到流量服务器。如果所需要的内容不是
敏感，然后可以从缓存提供服务。如果内容是
敏感且不可缓存，然后流量服务器获取内容
从源服务器(防火墙只允许流量服务器访问)
到原始服务器)。敏感内容存在于源上
服务器，安全地在防火墙内。

反向代理是如何工作的?
----------------------------

当浏览器发出请求时，它通常直接发送该请求
到原始服务器。当流量服务器处于反向代理模式时，它
在请求到达源服务器之前拦截请求。通常情况下,
这是通过为源服务器(即，
源服务器发布的主机名)，因此它可以解析流量
服务器的IP地址。当流量服务器被配置为源时
服务器，浏览器连接到流量服务器而不是源服务器
服务器。有关更多信息，请参见“HTTP反向代理”_。

. .注意::

为了避免DNS冲突，源服务器的主机名和它所发布的
主机名不能相同。

HTTP反向代理
==================

在反向代理模式下，流量服务器代表HTTP请求服务
一个web服务器。下图说明了流量服务器是如何反向的
代理模式提供来自客户端浏览器的HTTP请求。

. .图::/ admin / httprvs.jpg /静态图像
对齐:中心
:alt: HTTP反向代理

HTTP反向代理

上图展示了以下步骤:

. .下面的列表应该保持手动编号，因为条目对应于上图中的数字。

1. 客户机浏览器向被调用的主机发送一个HTTP请求
' www.host.com ' '端口80。流量服务器接收请求
因为它作为原始服务器(原始服务器的
发布的主机名解析到流量服务器)。

2. Traffic Server在:file: ' remap. '中定位映射规则。配置文件和
将请求重新映射到指定的源服务器(' ' realhost.com ' ')。

3.如果无法从缓存中提供请求，流量服务器将打开一个
连接到源服务器(或者更有可能的是，使用现有的
它预先建立的连接)，检索内容，以及可选的
把它保存起来以备将来使用。

4. 如果请求是缓存命中，并且内容在缓存中仍然是新鲜的，
或者由于步骤3，内容现在可以通过Traffic Server获得，
流量服务器将请求的对象从缓存发送给客户端
直接。

. .注意::

流量服务器，当更新自己的缓存从源服务器，将
同时将内容交付给客户端，同时更新其
缓存数据库。对包含请求对象的客户机的响应
会在流量服务器收到并处理完所有文件后开始吗
来自源服务器的响应头。

在配置HTTP反向代理之前，需要完成以下任务:

—在:文件“remap. conf”中创建映射规则。配置'文件(参见'创建
HTTP请求的映射规则' _)。::

地图http://www.host.com http://realhost.com

-启用反向代理选项(参考“启用HTTP反向代理”_)。

除了上述任务，您还可以“设置可选HTTP反向代理选项”_。

处理源服务器重定向响应
-----------------------------------------
=ron=


Origin servers often send redirect responses back to browsers
redirecting them to different pages. For example, if an origin server is
overloaded, then it might redirect browsers to a less loaded server.
Origin servers also redirect when web pages have moved to different
locations. When Traffic Server is configured as a reverse proxy, it must
readdress redirects from origin servers so that browsers are redirected
to Traffic Server and not to another origin server.

To readdress redirects, Traffic Server uses reverse-map rules. Unless
you have :ts:cv:`proxy.config.url_remap.pristine_host_hdr` enabled
(the default) you should generally set up a reverse-map rule for
each map rule. To create reverse-map rules, refer to `Using Mapping
Rules for HTTP Requests`_.

Using Mapping Rules for HTTP Requests
-------------------------------------

Traffic Server uses two types of mapping rules for HTTP reverse proxy.

map rule
~~~~~~~~

A *map rule* translates the URL in client requests into the URL where
the content is located. When Traffic Server is in reverse proxy mode and
receives an HTTP client request, it first constructs a complete request
URL from the relative URL and its headers. Traffic Server then looks for
a match by comparing the complete request URL with its list of target
URLs in :file:`remap.config`. For the request URL to match a target URL, the
following conditions must be true:

-  The scheme of both URLs must be the same.

-  The host in both URLs must be the same. If the request URL contains
   an unqualified hostname, then it will never match a target URL with a
   fully-qualified hostname.

-  The ports in both URLs must be the same. If no port is specified in a
   URL, then the default port for the scheme of the URL is used.

-  The path portion of the target URL must match a prefix of the request
   URL path.

If Traffic Server finds a match, then it translates the request URL into
the replacement URL listed in the map rule: it sets the host and path of
the request URL to match the replacement URL. If the URL contains path
prefixes, then Traffic Server removes the prefix of the path that
matches the target URL path and substitutes it with the path from the
replacement URL. If two mappings match a request URL, then Traffic
Server applies the first mapping listed in :file:`remap.config`.

reverse-map rule
~~~~~~~~~~~~~~~~

A *reverse-map rule* translates the URL in origin server redirect
responses to point to Traffic Server so that clients are redirected
to Traffic Server instead of accessing an origin server directly. For
example, if there is a directory ``/pub`` on an origin server at
``www.molasses.com`` and a client sends a request to that origin server
for ``/pub``, then the origin server might reply with a redirect by
sending the Header ``Location: http://realhost.com/pub/`` to let the
client know that it was a directory it had requested, not a document (a
common use of redirects is to normalize URLs so that clients can
bookmark documents properly).

Traffic Server uses ``reverse_map`` rules to prevent clients (that
receive redirects from origin servers) from bypassing Traffic Server and
directly accessing the origin servers. In many cases the client would be
hitting a wall because ``realhost.com`` actually does not resolve for
the client. (E.g.: Because it's running on a port shielded by a
firewall, or because it's running on a non-routable LAN IP)

Both map and reverse-map rules consist of a *target* (origin) URL and
a *replacement* (destination) URL. In a *map rule*, the target URL
points to Traffic Server and the replacement URL specifies where the
original content is located. In a *reverse-map rule*, the target URL
specifies where the original content is located and the replacement URL
points to Traffic Server. Traffic Server stores mapping rules in
:file:`remap.config` located in the Traffic Server ``config`` directory.

Creating Mapping Rules for HTTP Requests
----------------------------------------

To create mapping rules:

#. Enter the map and reverse-map rules into :file:`remap.config`.

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Enabling HTTP Reverse Proxy
---------------------------

=ron=
源服务器经常向浏览器发送重定向响应
将它们重定向到不同的页面。例如，如果一个源服务器是
重载时，它可能会将浏览器重定向到负载较低的服务器。
当网页移动到不同的地方时，源服务器也会重定向
的位置。当流量服务器被配置为反向代理时，它必须
从源服务器寻址重定向，以便浏览器被重定向
传输服务器，而不是另一个源服务器。

为了重定向地址，流量服务器使用反向映射规则。除非
你有:ts:简历:“proxy.config.url_remap。pristine_host_hdr的启用
(默认值)通常应该为
每个映射规则。要创建反向映射规则，请参阅“Using Mapping”
HTTP请求的_规则。

对HTTP请求使用映射规则
-------------------------------------

Traffic Server对HTTP反向代理使用两种映射规则。

映射规则
~ ~ ~ ~ ~ ~ ~ ~

一个*map规则*将客户端请求中的URL转换成URL
内容已定位。当流量服务器处于反向代理模式时
接收到HTTP客户机请求时，它首先构造一个完整的请求
相对URL及其头文件的URL。然后流量服务器寻找
通过将完整的请求URL与其目标列表进行比较来匹配
url:文件:“remap.config”。要使请求URL与目标URL匹配，则使用
以下条件必须为真:

—两个url的格式必须相同。

—两个url中的主机必须相同。如果请求URL包含
一个非限定的主机名，那么它将永远不会与目标URL匹配
完全限定主机名。

—两个url中的端口必须相同。如果a中没有指定端口
URL，则使用URL方案的缺省端口。

—目标URL的路径部分必须匹配请求的前缀
URL路径。

如果流量服务器找到匹配项，它就会将请求URL转换为
映射规则中列出的替换URL:它设置的主机和路径
与替换URL匹配的请求URL。如果URL中包含路径
前缀，然后流量服务器删除该路径的前缀
匹配目标URL路径，并使用来自
替换URL。如果两个映射匹配一个请求URL，则为流量
Server应用:file: ' remap.config '中列出的第一个映射。

逆向映射规则
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

反向映射规则*在源服务器重定向中转换URL
响应指向流量服务器，以便客户端被重定向
而不是直接访问源服务器。为
例如，如果在源服务器上有一个目录' ' /pub ' '
' ' www.molasses.com ' '然后客户机向该源服务器发送请求
对于' ' /pub ' '，则源服务器可能会返回一个重定向by
发送头部' '位置:http://realhost.com/pub/ ' '让
客户机知道它请求的是一个目录，而不是一个文档(a
重定向的常见用途是规范化url，这样客户端就可以
书签文件正确)。

流量服务器使用' ' reverse_map ' '规则来阻止客户端
从源服务器接收重定向)从绕过流量服务器和
直接访问源服务器。在许多情况下，客户会
撞墙是因为“realhost.com”实际上并没有解决
客户端。例如:因为它运行在一个被a屏蔽的端口上
防火墙，或者因为它运行在一个不可路由的局域网IP上)

映射规则和反向映射规则都由一个*target* (origin) URL和
一个*替换*(目的地)URL。在*map规则*中，目标URL
指向流量服务器，替换URL指定
原创内容被定位。在*反向映射规则*中，目标URL
指定原始内容的位置和替换URL
指向流量服务器。流量服务器存储映射规则
:文件:“重新映射。位于流量服务器“配置”目录中的配置。

为HTTP请求创建映射规则
----------------------------------------

创建映射规则:

#。在:file: ' remap.config '中输入映射规则和反向映射规则。

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

启用HTTP反向代理
---------------------------
=ron=


To enable HTTP reverse proxy:

#. Edit :ts:cv:`proxy.config.reverse_proxy.enabled` in :file:`records.config`. ::

    CONFIG proxy.config.reverse_proxy.enabled INT 1

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Setting Optional HTTP Reverse Proxy Options
-------------------------------------------

Traffic Server provides several reverse proxy configuration options in
:file:`records.config` that enable you to:

-  Configure Traffic Server to retain the client host header information
   in a request during translation.
   See :ts:cv:`proxy.config.url_remap.pristine_host_hdr`.

-  Configure Traffic Server to serve requests only to the origin servers
   listed in the mapping rules. As a result, requests to origin servers
   not listed in the mapping rules are not served.
   See :ts:cv:`proxy.config.url_remap.remap_required`.

-  Specify an alternate URL to which incoming requests from older clients ,such
   as ones that do not provide ``Host`` headers, are directed.
   See :ts:cv:`proxy.config.header.parse.no_host_url_redirect`.

Run the command :option:`traffic_ctl config reload` to apply any of these configuration
changes.

Redirecting HTTP Requests
=========================

You can configure Traffic Server to redirect HTTP requests without
having to contact any origin servers. For example, if you redirect all
requests for ``http://www.ultraseek.com`` to
``http://www.server1.com/products/portal/search/``, then all HTTP
requests for ``www.ultraseek.com`` go directly to
``www.server1.com/products/portal/search``.

You can configure Traffic Server to perform permanent or temporary
redirects. *Permanent redirects* notify the browser of the URL change
(by returning the HTTP status code ``301``) so that the browser can
update bookmarks. *Temporary redirects* notify the browser of the URL
change for the current request only (by returning the HTTP status code
``307`` ).

To set redirect rules:

#. For each redirect you want to set enter a mapping rule in :file:`remap.config`.

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Example
-------

The following permanently redirects all HTTP requests for
``www.server1.com`` to ``www.server2.com``: ::

    redirect http://www.server1.com http://www.server2.com



=ron=
启用HTTP反向代理。

#。编辑:ts:简历:“proxy.config.reverse_proxy。”:文件:“records.config”启用。::

配置proxy.config.reverse_proxy。启用INT 1

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

设置可选HTTP反向代理选项
-------------------------------------------

流量服务器提供几个反向代理配置选项
:文件:记录。配置'，使您能够:

—配置流量服务器，保留客户端主机头信息
在翻译过程中的请求。
看:ts:简历:“proxy.config.url_remap.pristine_host_hdr”。

—配置“流量服务器”，只向源服务器发送请求
在映射规则中列出。因此，请求源服务器
映射规则中未列出的不服务。
看:ts:简历:“proxy.config.url_remap.remap_required”。

-指定一个替代URL，该URL的传入请求来自较老的客户端，例如
如不提供' ' Host ' '头文件，则被定向。
看:ts:简历:“proxy.config.header.parse.no_host_url_redirect”。

运行option: ' traffic_ctl config reload '命令应用这些配置
的变化。

将HTTP请求
=========================

您可以配置流量服务器重定向HTTP请求
必须联系任何源服务器。例如，如果你重定向all
对“http://www.ultraseek.com”的请求
' http://www.server1.com/products/portal/search/ ' '，然后所有HTTP
对“www.ultraseek.com”的请求直接到
“www.server1.com/products/portal/search”。

流量服务器可以配置为永久或临时
重定向。*永久重定向*通知浏览器的URL改变
(通过返回HTTP状态码' ' 301 ' ')，这样浏览器就可以
更新书签。*通知浏览器的URL
仅更改当前请求(通过返回HTTP状态代码)
' ' 307 ')。

设置重定向规则。

#。对于要设置的每个重定向，请在:file: ' remap.config '中输入映射规则。

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

例子
-------

以下内容将永久地重定向所有的HTTP请求
' www.server1.com ' '到' www.server2.com ' ':::

重定向http://www.server1.com http://www.server2.com
=ron=

