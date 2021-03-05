.. _explicit-proxy-caching:

Explicit Proxy Caching
**********************

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

If you want to use Traffic Server as an explicit proxy cache, you must
configure client software (i.e., browsers) to send requests directly to
Traffic Server.

If you do not configure Traffic Server to use the transparency option
(with which client requests are intercepted en route to origin servers
by a switch/router and rerouted to the Traffic Server machine), then
clients must configure their web browsers to send HTTP requests to the
Traffic Server proxy cache by configuring their browsers to download
proxy configuration instructions from a :ref:`PAC file <using-a-pack-file>`
(Proxy Auto-Configuration file).

Configuring Browsers Manually
=============================

To manually configure a browser to send HTTP requests to Traffic Server,
clients must provide the following information:

-  The fully-qualified hostname or IP address of the Traffic Server node
-  The Traffic Server proxy server port (by default, 8080)

In addition, clients can specify not to use Traffic Server for certain
sites - in such cases, requests to the listed sites go directly to the
origin server. The procedures for manual configuration vary among
browser versions; refer to specific browser documentation for complete
proxy configuration instructions. You do not need to set any special
configuration options on Traffic Server if you want to accept requests
from manually-configured browsers.

.. _using-a-pack-file:

Using a PAC File
================

A *PAC file* is a specialized JavaScript function definition that a
browser calls to determine how requests are handled. Clients must
specify (in their browser settings) the URL from which the PAC file is
loaded. You can store a PAC file on Traffic Server (or on any server in
your network) and then provide the URL for this file to your clients.

Sample PAC File
---------------

The following sample PAC file instructs browsers to connect directly to
all hosts without a fully-qualified domain name and to all hosts in the
local domain. All other requests go to the Traffic Server named
``myproxy.company.com``.::

    function FindProxyForURL(url, host)
    {
      if (isPlainHostName(host)) || (localHostOrDomainIs(host, ".company.com")) {
        return "DIRECT";
      }
      else
        return "PROXY myproxy.company.com:8080; DIRECT";
    }


=ron=
. ._explicit-proxy-caching:

显式的代理缓存
**********************

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

如果您想使用Traffic Server作为显式代理缓存，则必须
配置客户端软件(即浏览器)以直接发送请求
交通服务器。

如果您没有配置流量服务器使用透明选项
(客户端请求在到达源服务器的途中被拦截
通过交换机/路由器并重新路由到流量服务器机器)，然后
客户端必须配置他们的web浏览器来发送HTTP请求到
流量服务器代理缓存通过配置其浏览器来下载
引用:' PAC file <using-a-pack-file> '</using-a-pack-file>
(代理自动配置文件)。

手动配置浏览器
=============================

手动配置浏览器向流量服务器发送HTTP请求，
客户必须提供以下信息:

—流量服务器节点的全限定主机名或IP地址
—流量服务器代理服务器端口(默认为8080)

另外，客户端可以指定不使用流量服务器
站点——在这种情况下，对列出的站点的请求直接转到
原始服务器。手动配置的步骤各不相同
浏览器版本;请参考特定的浏览器文档以获取完整信息
代理配置指令。您不需要设置任何特殊的
如果您想接受请求，流量服务器上的配置选项
从手动配置浏览器。

. ._using-a-pack-file:

使用PAC文件
================

一个*PAC文件*是一个专门的JavaScript函数定义
浏览器调用以确定如何处理请求。客户端必须
(在浏览器设置中)指定PAC文件所在的URL
加载。您可以存储一个PAC文件在流量服务器(或任何服务器
然后将该文件的URL提供给客户端。

PAC文件示例
---------------

下面的示例PAC文件指示浏览器直接连接到
没有完全合格域名的所有主机和
当地的域。所有其他请求都将转到名为
' ' myproxy.company.com ' '。::

函数FindProxyForURL (url、主机)
{
if (isPlainHostName(host)) || (localHostOrDomainIs(host， ".company.com")) {
返回“直接”;
}
其他的
返回“代理myproxy.company.com: 8080;直接”;
}
=ron=
