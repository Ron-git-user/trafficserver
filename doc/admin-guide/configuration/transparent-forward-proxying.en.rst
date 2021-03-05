.. _forward-proxy:

Forward Proxy
*************

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

The Apache Traffic Server is a general purpose proxy, configurable as both a
reverse and forward proxy.

A forward proxy can be used as a central tool in your infrastructure
to access the web and it may be combined with a cache to lower your overall
bandwidth usage. Forward proxies act as a gatekeeper between client browsers
on your local network and all (or some, at your configuration's discretion)
web sites accessed by those clients. The forward proxy will receive the
HTTP requests, perform any filtering or request alteration rules you
establish, and when appropriate forward the request on to its destination
website. The response will return through your proxy, where it may optionally
be cached and/or modified, and then returned to the original client.

There are two modes in which your forward proxy may operate:

Forward Proxy
    Each client must be configured explicitly to use the forward proxy. Client
    browsers will be aware of the fact they are using a proxy and will form their
    HTTP requests appropriately. This results in the initial HTTP command being
    issued with fully qualified URIs that contain the destination hostname::

        GET http://example.com/index.php?id=123 HTTP/1.1

Transparent Proxy
    The use of a transparent proxy is typically done in concert with network
    routing rules which redirect all outbound HTTP traffic through your proxy.
    Clients will behave, and form their HTTP requests, as if they are contacting
    the remote site directly, and will not be aware of the existence of a proxy
    server in between themselves and the remote servers. HTTP requests will be
    generated per their usual form, with only paths in the command and a
    separate Host request header::

        GET /index?id=123 HTTP/1.1
        Host: example.com

Apache Traffic Server may be configured to operate as both a forward and
a transparent proxy simultaneously.


=ron=
. ._forward-proxy:

转发代理
*************

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

Apache流量服务器是一种通用代理，可以配置为
反向和正向代理。

转发代理可以作为基础架构中的中心工具使用
来访问网络，它可以与缓存结合来降低你的整体
带宽的使用。转发代理充当客户端浏览器之间的看门人
在您的本地网络和所有(或部分，由您的配置决定)
这些客户机访问的web站点。转发代理将接收
HTTP请求时，执行任何过滤或请求更改规则
建立并在适当的时候将请求转发到其目的地
的网站。响应将通过代理返回，可以选择返回
被缓存和/或修改，然后返回到原始客户机。

有两种模式下，你的转发代理可能操作:

转发代理
必须显式地配置每个客户机以使用正向代理。客户端
浏览器会意识到他们正在使用代理，并形成他们的
适当的HTTP请求。这将导致初始的HTTP命令
使用包含目标主机名::的完全限定uri发出

得到http://example.com/index.php?id = 123 HTTP / 1.1

透明代理
透明代理的使用通常与网络一起完成
通过代理重定向所有出站HTTP流量的路由规则。
客户端将表现出与正在进行联系一样的行为，并形成HTTP请求
直接访问远程站点，并不会意识到代理的存在
服务器在自己和远程服务器之间。HTTP请求将
按照它们通常的形式生成，命令中只有路径和a
单独的主机请求头::

/索引吗?id = 123 HTTP / 1.1
主持人:example.com

Apache流量服务器可以配置为作为转发和
同时使用透明代理。
=ron=


Proxy Configuration
===================

Configuring basic forward proxy operation in Traffic Server is quite simple
and straightforward.

1. Permit Traffic Server to process requests for hosts not explicitly configured
   in the remap rules, by modifying :ts:cv:`proxy.config.url_remap.remap_required`
   in :file:`records.config`::

        CONFIG proxy.config.url_remap.remap_required INT 0

2. *Optional*: If Traffic Server will be operating strictly as a forward proxy,
   you will want to disable reverse proxy support by modifying
   :ts:cv:`proxy.config.reverse_proxy.enabled` in :file:`records.config`::

        CONFIG proxy.config.reverse_proxy.enabled INT 0

You may also want to consider some of these configuration options:

- Setting :ts:cv:`proxy.config.http.no_dns_just_forward_to_parent` determines which
  host will be used for DNS resolution.

- Proxy Authentication can be enabled or disabled with
  :ts:cv:`proxy.config.http.forward.proxy_auth_to_parent` should you also be
  employing a proxy cache.

- The client request header X-Forwarded-For may be toggled with
  :ts:cv:`proxy.config.http.insert_squid_x_forwarded_for`.

- The client request header Forwarded may be configured with
  :ts:cv:`proxy.config.http.insert_forwarded`.

Client Configuration
====================

If you are operating your proxy in transparent mode, your clients should require
no special proxy-related configuration.

If you are operating in explicit forward proxy mode, without automatic routing
rules on your network to direct all outbound traffic through the proxy, your
client browsers will need to be directed to the proxy. This may be accomplished
in two different ways.

Clients may be configured to use the default ``8080`` port on your Traffic Server
host as a proxy. This will result in all requests from that client browser being
issued through the single forward proxy as configured.

Security Considerations
=======================

It's important to note that once your Apache Traffic Server is configured as a
forward proxy it will indiscriminately accept proxy requests from anyone. If it
is reachable from the Internet, then you have configured an *Open Proxy*.

This is generally not desirable, as it will permit anyone to potentially use
your network as the source of traffic to sites of their choosing. To avoid
this, you'll have to make sure your proxy server is either only reachable from
within your private network or is secured by firewall rules that permit only
those you wish to have access to the proxy.


=ron=
代理配置
===================

在流量服务器中配置基本的转发代理操作非常简单
明了。

1. 允许流量服务器处理对未显式配置的主机的请求
在重映射规则中，通过修改:ts:cv: ' proxy.config. url_remmap .remap_required '
:文件:“records.config”::

配置proxy.config.url_remap。remap_required INT 0

2. *可选*:如果流量服务器将严格作为转发代理运行，
您将希望通过修改来禁用反向代理支持
ts:简历:“proxy.config.reverse_proxy。启用”:文件:“records.config”::

配置proxy.config.reverse_proxy。启用INT 0

你也可以考虑以下的一些配置选项:

——设置:ts:简历:“proxy.config.http。no_dns_just_forward_to_parent的决定
主机将用于DNS解析。

—启用或禁用代理认证
ts:简历:“proxy.config.http.forward。proxy_auth_to_parent '也应该是
使用代理缓存。

—客户端请求头X-Forwarded-For可以切换
ts:简历:“proxy.config.http.insert_squid_x_forwarded_for”。

—转发的客户端请求头可以配置为
ts:简历:“proxy.config.http.insert_forwarded”。

客户端配置
====================

如果您在透明模式下操作代理，您的客户端应该要求
没有与代理相关的特殊配置。

如果您使用的是显式转发代理模式，而没有自动路由
您的网络规则，以引导所有出站流量通过代理，您的
客户端浏览器将需要被定向到代理。这是可以做到的
有两种不同的方式。

客户端可能被配置为使用通信服务器上的默认端口“8080”
主机作为代理。这将导致来自该客户机浏览器的所有请求都是
通过配置的单个转发代理发出。

安全注意事项
=======================

重要的是要注意，一旦您的Apache流量服务器配置为a
转发代理它将不加区别地接受来自任何人的代理请求。如果它
是可从Internet访问的，那么您已经配置了一个*开放代理*。

这通常是不可取的，因为它允许任何人潜在地使用
你的网络是他们选择的网站的流量来源。为了避免
因此，您必须确保您的代理服务器只能从
在您的私人网络中，或由防火墙规则保护，只允许
您希望访问代理的用户。
=ron=
