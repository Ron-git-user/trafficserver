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

.. _http-proxy-caching:

HTTP Proxy Caching
******************

HTTP proxy caching enables you to store copies of frequently-accessed web
objects (such as documents, images, and articles) and then serve this
information to users on demand. It improves performance and frees up
Internet bandwidth for other tasks.

.. toctree::
   :maxdepth: 2

Understanding HTTP Web Proxy Caching
====================================

Internet users direct their requests to web servers all over the
Internet. A caching server must act as a *web proxy server* so it can
serve those requests. After a web proxy server receives requests for web
objects, it either serves the requests or forwards them to the *origin
server* (the web server that contains the original copy of the
requested information). The Traffic Server proxy supports *explicit
proxy caching*, in which the user's client software must be configured
to send requests directly to the Traffic Server proxy. The following
overview illustrates how Traffic Server serves a request.

#. Traffic Server receives a client request for a web object.

#. Using the object address, Traffic Server tries to locate the
   requested object in its object database (*cache*).

#. If the object is in the cache, then Traffic Server checks to see if
   the object is fresh enough to serve. If it is fresh, then Traffic
   Server serves it to the client as a *cache hit* (see the figure
   below).

   .. figure:: /static/images/admin/cache_hit.jpg
      :align: center
      :alt: A cache hit

      A cache hit

#. If the data in the cache is stale, then Traffic Server connects to
   the origin server and checks if the object is still fresh (a
   :term:`revalidation`). If it is, then Traffic Server immediately sends
   the cached copy to the client.

#. If the object is not in the cache (a *cache miss*) or if the server
   indicates the cached copy is no longer valid, then Traffic Server
   obtains the object from the origin server. The object is then
   simultaneously streamed to the client and the Traffic Server local
   cache (see the figure below). Subsequent requests for the object can
   be served faster because the object is retrieved directly from cache.

   .. figure:: /static/images/admin/cache_miss.jpg
      :align: center
      :alt: A cache miss

      A cache miss

Caching is typically more complex than the preceding overview suggests.
In particular, the overview does not discuss how Traffic Server ensures
freshness, serves correct HTTP alternates, and treats requests for
objects that cannot or should not be cached. The following sections discuss
these issues in greater detail.

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

. ._http-proxy-caching:

HTTP代理缓存
******************

HTTP代理缓存使您能够存储经常访问的web的副本
对象(如文档、图像和文章)，然后为其提供服务
根据用户需求提供信息。它提高了性能并释放了资源
用于其他任务的互联网带宽。

. .toctree::
: maxdepth: 2

理解HTTP Web代理缓存
====================================

互联网用户直接将他们的请求发送到遍布全国的web服务器
互联网。缓存服务器必须扮演一个web代理服务器的角色
这些请求服务。web代理服务器接收到web请求后
对象，它要么为请求服务，要么将请求转发到*origin
服务器* (web服务器，包含的原始副本
请求的信息)。流量服务器代理支持*显式
代理缓存*，在其中必须配置用户的客户端软件
直接向流量服务器代理发送请求。以下
概述说明了流量服务器如何服务请求。

#。流量服务器接收一个web对象的客户端请求。

#。使用对象地址，流量服务器试图定位
在对象数据库(*cache*)中被请求的对象。

#。如果对象在缓存中，则流量服务器检查是否
这东西新鲜得足以上桌。如果它是新鲜的，那么交通
服务器将它作为*缓存命中*服务给客户端(见图)
下文)。

. .图::/ admin / cache_hit.jpg /静态图像
对齐:中心
:alt:缓存命中

一个缓存命中

#。如果缓存中的数据已经过期，那么流量服务器将连接到
源服务器并检查对象是否仍然是新鲜的(a
词:“重新生效”)。如果是，那么流量服务器立即发送
缓存到客户机的副本。

#。如果对象不在缓存中(a *cache miss*)或服务器
表示缓存的副本不再有效，然后是流量服务器
从源服务器获取对象。对象是
同时流到客户端和本地流量服务器
缓存(见下图)。对该对象的后续请求可以
因为直接从缓存中检索对象，所以可以更快地提供服务。

. .图::/ admin / cache_miss.jpg /静态图像
对齐:中心
:alt: cache miss

缓存错过

缓存通常比前面介绍的要复杂得多。
特别是，概述没有讨论Traffic Server如何确保
新鲜，服务正确的HTTP替代，并处理请求
不能或不应该缓存的对象。下面几节讨论
更详细地讨论这些问题。
=ron=



.. _ensuring-cached-object-freshness:

Ensuring Cached Object Freshness
================================

When Traffic Server receives a request for a web object, it first tries
to locate the requested object in its cache. If the object is in cache,
then Traffic Server checks to see if the object is fresh enough to
serve. For HTTP objects, Traffic Server supports optional
author-specified expiration dates. Traffic Server adheres to these
expiration dates; otherwise, it picks an expiration date based on how
frequently the object is changing and on administrator-chosen freshness
guidelines. Objects can also be revalidated by checking with the origin
server to see if an object is still fresh.

HTTP Object Freshness
---------------------

Traffic Server determines whether an HTTP object in the cache is fresh
by checking the following conditions in order:

-  **Checking the** ``Expires`` **or** ``max-age`` **header**

   Some HTTP objects contain ``Expires`` headers or ``max-age`` headers
   that explicitly define how long the object can be cached. Traffic
   Server compares the current time with the expiration time to
   determine if the object is still fresh.

-  **Checking the** ``Last-Modified`` **/** ``Date`` **header**

   If an HTTP object has no ``Expires`` header or ``max-age`` header,
   then Traffic Server can calculate a freshness limit using the
   following formula::

      freshness_limit = ( date - last_modified ) * 0.10

   where *date* is the date in the object's server response header
   and *last_modified* is the date in the ``Last-Modified`` header.
   If there is no ``Last-Modified`` header, then Traffic Server uses the
   date the object was written to cache. The value ``0.10`` (10 percent)
   can be increased or reduced to better suit your needs. Refer to
   `Modifying Aging Factor for Freshness Computations`_.

   The computed freshness limit is bound by a minimum and maximum value.
   Refer to `Setting Absolute Freshness Limits`_ for more information.

-  **Checking the absolute freshness limit**

   For HTTP objects that do not have ``Expires`` headers or do not have
   both ``Last-Modified`` and ``Date`` headers, Traffic Server uses a
   maximum and minimum freshness limit. Refer to
   `Setting Absolute Freshness Limits`_.

-  **Checking revalidate rules in** :file:`cache.config`

   Revalidate rules apply freshness limits to specific HTTP objects. You
   can set freshness limits for objects originating from particular
   domains or IP addresses, objects with URLs that contain specified
   regular expressions, objects requested by particular clients, and so
   on. Refer to :file:`cache.config`.

Modifying Aging Factor for Freshness Computations
-------------------------------------------------

If an object does not contain any expiration information, then Traffic
Server can estimate its freshness from the ``Last-Modified`` and
``Date`` headers. By default, Traffic Server stores an object for 10% of
the time that elapsed since it last changed. You can increase or reduce
the percentage according to your needs.

To modify the aging factor for freshness computations:

#. Change the value for :ts:cv:`proxy.config.http.cache.heuristic_lm_factor`.

#. Run the :option:`traffic_ctl config reload` command to apply the configuration changes.

Setting Absolute Freshness Limits
---------------------------------

Some objects do not have ``Expires`` headers or do not have both
``Last-Modified`` and ``Date`` headers. To control how long these
objects are considered fresh in the cache, specify an *absolute
freshness limit*.

To specify an absolute freshness limit:

#. Edit the variables :ts:cv:`proxy.config.http.cache.heuristic_min_lifetime`
   and :ts:cv:`proxy.config.http.cache.heuristic_max_lifetime` in
   :file:`records.config`.

#. Run the :option:`traffic_ctl config reload` command to apply the configuration changes.

Specifying Header Requirements
------------------------------

To further ensure freshness of the objects in the cache, configure
Traffic Server to cache only objects with specific headers. By default,
Traffic Server caches all objects (including objects with no headers);
you should change the default setting only for specialized proxy
situations. If you configure Traffic Server to cache only HTTP objects
with ``Expires`` or ``max-age`` headers, then the cache hit rate will be
noticeably reduced (since very few objects will have explicit expiration
information).

=ron=
. ._ensuring-cached-object-freshness:

确保缓存的对象新鲜度
================================

当流量服务器接收到对web对象的请求时，它首先尝试
在其缓存中定位被请求的对象。如果对象在缓存中，
然后，流量服务器检查对象是否足够新鲜
服务。对于HTTP对象，Traffic Server支持可选
author-specified过期日期。流量服务器遵循这些
保质期;否则，它会根据过期方式选择一个过期日期
对象经常是变化的，并且由管理员选择新鲜度
指导方针。对象也可以通过检查origin来重新验证
查看对象是否仍然是新鲜的。

HTTP对象新鲜
---------------------

流量服务器确定缓存中的HTTP对象是否新鲜
按顺序检查以下条件:

- * *检查* *“到期”“* *或* *的“信息”“* *头* *

一些HTTP对象包含' ' Expires ' ' '头文件或' ' max-age ' '头文件
显式定义对象可以缓存多长时间。交通
服务器将当前时间与过期时间进行比较
确定对象是否仍然是新鲜的。

- * *检查* *“最后修改 `` **/** `` “* *头* *

如果HTTP对象没有' Expires ' '头或者' max-age '头，
然后流量服务器可以计算新鲜限制使用
下面的公式:

freshness_limit = (date - last_modified) * 0.10

其中*date*是对象的服务器响应头中的日期
*last_modified*是Last-Modified头文件中的日期。
如果没有' ' Last-Modified ' '报头，那么流量服务器使用
写入缓存对象的日期。值“0.10”(10%)
可以增加或减少，以更好地满足您的需求。指
“为计算新鲜度修改老化因子”_。

计算的新鲜度限制受到最小值和最大值的限制。
更多信息请参考“设置绝对新鲜度限制”_。

- **检查绝对新鲜度限制**

对于没有' ' Expires ' '报头或没有' ' Expires ' '报头的HTTP对象
无论是' Last-Modified ' '和' Date ' '头，流量服务器使用
最大和最小新鲜度限制。指
“设置绝对新鲜度限制”_。

- **检查重新验证规则在**:文件:' cache.config '

重新验证规则将新鲜度限制应用于特定的HTTP对象。你
可以为来自特定的对象设置新鲜度限制吗
域或IP地址，包含指定的url的对象
正则表达式，特定客户端请求的对象，等等
上。参考文件:“cache.config”。

修改新鲜度计算的老化因子
-------------------------------------------------

如果一个对象不包含任何过期信息，那么流量
服务器可以根据“Last-Modified”和“Last-Modified”来估计它的新鲜度
“日期”“头。默认情况下，流量服务器将对象存储为10%
从它最后一次改变后经过的时间。你可以增加或减少
百分比根据您的需要而定。

修改老化因子的新鲜度计算:

#。修改:ts:cv: ' proxy.config.http.cache.heuristic_lm_factor '的值。

#。执行:option: ' traffic_ctl config reload '命令应用配置更改。

设置绝对新鲜度限制
---------------------------------

有些对象没有' ' Expires ' '头文件或者两者都没有
' ' Last-Modified ' '和' Date ' '头文件。来控制这些
对象在缓存中被认为是新鲜的，请指定*absolute
新鲜限制*。

指定绝对新鲜度限制:

#。编辑变量:ts:cv: ' proxy.config.http.cache.heuristic_min_lifetime '
和:ts:简历:“proxy.config.http.cache。heuristic_max_lifetime”
:文件:“records.config”。

#。执行:option: ' traffic_ctl config reload '命令应用配置更改。

指定标头的要求
------------------------------

要进一步确保缓存中的对象是新鲜的，请进行配置
流量服务器只缓存具有特定标头的对象。默认情况下,
流量服务器缓存所有对象(包括没有头的对象);
您应该仅为专用代理更改默认设置
的情况。如果您将流量服务器配置为仅缓存HTTP对象
使用' ' Expires ' '或' ' max-age ' '头文件，缓存命中率将会是
显著减少(因为很少有对象会有显式过期
信息)。
=ron=



To configure Traffic Server to cache objects with specific headers:

#. Change the value for :ts:cv:`proxy.config.http.cache.required_headers`
   in :file:`records.config`.

#. Run the :option:`traffic_ctl config reload` command to apply the configuration changes.

Cache-Control Headers
---------------------

Even though an object might be fresh in the cache, clients or servers
often impose their own constraints that preclude retrieval of the object
from the cache. For example, a client might request that a object not
be retrieved from a cache, or if it does allow cache retrieval, then it
cannot have been cached for more than 10 minutes.

Traffic Server bases the servability of a cached object on ``Cache-Control``
headers that appear in both client requests and server responses. The following
``Cache-Control`` headers affect whether objects are served from cache:

-  The ``no-cache`` header, sent by clients, tells Traffic Server that
   it should not serve any objects directly from the cache. When present in a
   client request, Traffic Server will always obtain the object from the
   origin server. You can configure Traffic Server to ignore client
   ``no-cache`` headers. Refer to `Configuring Traffic Server to Ignore Client no-cache Headers`_
   for more information.

-  The ``max-age`` header, sent by servers, is compared to the object
   age. If the age is less than ``max-age``, then the object is fresh
   and can be served from the Traffic Server cache.

-  The ``min-fresh`` header, sent by clients, is an *acceptable
   freshness tolerance*. This means that the client wants the object to
   be at least this fresh. Unless a cached object remains fresh at least
   this long in the future, it is revalidated.

-  The ``max-stale`` header, sent by clients, permits Traffic Server to
   serve stale objects provided they are not too old. Some browsers
   might be willing to take slightly stale objects in exchange for
   improved performance, especially during periods of poor Internet
   availability.

Traffic Server applies ``Cache-Control`` servability criteria after HTTP
freshness criteria. For example, an object might be considered fresh but will
not be served if its age is greater than its ``max-age``.

Revalidating HTTP Objects
-------------------------

When a client requests an HTTP object that is stale in the cache,
Traffic Server revalidates the object. A *revalidation* is a query to
the origin server to check if the object is unchanged. The result of a
revalidation is one of the following:

-  If the object is still fresh, then Traffic Server resets its
   freshness limit and serves the object.

-  If a new copy of the object is available, then Traffic Server caches
   the new object (thereby replacing the stale copy) and simultaneously
   serves the object to the client.

-  If the object no longer exists on the origin server, then Traffic
   Server does not serve the cached copy.

-  If the origin server does not respond to the revalidation query, then
   Traffic Server serves the stale object along with a
   ``111 Revalidation Failed`` warning.

By default, Traffic Server revalidates a requested HTTP object in the
cache if it considers the object to be stale. Traffic Server evaluates
object freshness as described in `HTTP Object Freshness`_.
You can reconfigure how Traffic Server evaluates freshness by selecting
one of the following options:

*Traffic Server considers all HTTP objects in the cache to be stale:*
    Always revalidate HTTP objects in the cache with the origin server.

*Traffic Server considers all HTTP objects in the cache to be fresh:*
    Never revalidate HTTP objects in the cache with the origin server.

*Traffic Server considers all HTTP objects without* ``Expires`` *or* ``Cache-control`` *headers to be stale:*
    Revalidate all HTTP objects without ``Expires`` or ``Cache-Control`` headers.

To configure how Traffic Server revalidates objects in the cache, you
can set specific revalidation rules in :file:`cache.config`.

To configure revalidation options

#. Edit the variable :ts:cv:`proxy.config.http.cache.when_to_revalidate`
   in :file:`records.config`.

#. Run the :option:`traffic_ctl config reload` command to apply the configuration changes.

.. _pushing-content-into-the-cache:

Pushing Content into the Cache
==============================

=ron=
配置流量服务器来缓存具有特定头的对象:

#。修改:ts:cv: ' proxy.config.http.cache.required_headers '的值
:文件:“records.config”。

#。执行:option: ' traffic_ctl config reload '命令应用配置更改。

cache - control头信息
---------------------

即使对象在缓存、客户端或服务器中可能是新鲜的
通常强加它们自己的约束，阻止检索对象
从缓存中。例如，客户端可能请求一个对象不
从缓存中检索，或者如果它允许缓存检索，那么它
缓存时间不能超过10分钟。

流量服务器基于' ' Cache-Control ' '的缓存对象的可服务性
同时出现在客户端请求和服务器响应中的标头。以下
' ' cache - control ' '头文件会影响是否从缓存中提供对象:

客户端发送的' ' no-cache ' '报头告诉流量服务器
它不应该直接从缓存中提供任何对象。当出现在
客户端请求时，流量服务器总会从该对象中获取
原始服务器。可以配置流量服务器忽略客户端
“no - cache的头。请参考'配置流量服务器忽略客户端no-cache头' _
为更多的信息。

- ' max-age ' '报头，由服务器发送，与对象比较
的年龄。如果age小于' ' max-age ' '，则对象是新鲜的
并且可以从流量服务器缓存中提供服务。

—客户端发送的“min-fresh”报头是可以接受的*
新鲜的宽容。这意味着客户端希望对象
至少要这么新鲜。除非缓存的对象至少保持新鲜
在未来的很长一段时间里，它将被重新验证。

—“max-stale”报头由客户端发送，允许流量服务器访问
提供陈旧的对象，只要它们不是太老。一些浏览器
可能会愿意拿一些陈旧的东西来交换
改进的性能，特别是在互联网差的时期
可用性。

流量服务器在HTTP后应用“缓存控制”的可服务性标准
新鲜的标准。例如，一个对象可能被认为是新鲜的，但将会
如果其年龄大于其“max-age”，则不提供服务。

重新验证HTTP对象
-------------------------

当客户端请求缓存中过期的HTTP对象时，
流量服务器重新验证对象。revalidation*是对
源服务器来检查对象是否没有改变。a的结果
再验证是以下其中一种:

—如果对象仍然是新鲜的，则流量服务器重置其
限制新鲜度，服务对象。

—如果对象的新副本可用，那么流量服务器就会缓存
新对象(从而替换陈旧的副本)
将对象服务给客户端。

—如果该对象在源服务器上已经不存在，则为流量
服务器不提供缓存的副本。

—如果源服务器没有响应重新验证请求，则
流量服务器为陈旧的对象提供服务
' 111重新验证失败' '警告。

默认情况下，流量服务器重新验证请求的HTTP对象
如果认为对象已过期，则缓存。交通服务器评估
对象新鲜度，如' HTTP对象新鲜度' _所述。
通过选择，可以重新配置流量服务器评估新鲜度的方式
下列选择之一:

*Traffic Server认为缓存中的所有HTTP对象都是过期的
总是使用源服务器重新验证缓存中的HTTP对象。

*Traffic Server认为缓存中的所有HTTP对象都是新鲜的
永远不要用源服务器重新验证缓存中的HTTP对象。

*Traffic Server认为所有没有* ' ' Expires ' ' ' *或* ' ' Cache-control ' ' *报头的HTTP对象是过期的:*
重新验证所有没有' ' Expires ' '或' ' Cache-Control ' '报头的HTTP对象。

要配置Traffic Server如何重新验证缓存中的对象，您需要
可以在:file: ' cache.config '中设置特定的重新验证规则。

配置重新验证选项

#。编辑变量:ts:cv: ' proxy.config.http.cache.when_to_revalidate '
:文件:“records.config”。

#。执行:option: ' traffic_ctl config reload '命令应用配置更改。

. ._pushing-content-into-the-cache:

将内容推入缓存
==============================
=ron=



Traffic Server supports the HTTP ``PUSH`` method of content delivery.
Using HTTP ``PUSH``, you can deliver content directly into the cache
without client requests.

Configuring Traffic Server for PUSH Requests
--------------------------------------------

Before you can deliver content into your cache using HTTP ``PUSH``, you
must configure Traffic Server to accept ``PUSH`` requests.

#. Edit :file:`ip_allow.yaml` to allow ``PUSH`` from the appropriate addresses.

#. Update :ts:cv:`proxy.config.http.push_method_enabled` in
   :file:`records.config`::

        CONFIG proxy.config.http.push_method_enabled INT 1

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Understanding HTTP PUSH
-----------------------

``PUSH`` uses the HTTP 1.1 message format. The body of a ``PUSH``
request contains the response header and response body that you want to
place in the cache. The following is an example of a ``PUSH`` request::

   PUSH http://www.company.com HTTP/1.0
   Content-length: 84

   HTTP/1.0 200 OK
   Content-type: text/html
   Content-length: 17

   <HTML>
   a
   </HTML>

.. important::

   Your ``PUSH`` headers must include ``Content-length``, the value for which
   must include both headers and body byte counts. The value is not optional,
   and an improper (too large or too small) value will result in undesirable
   behavior.

Tools that will help manage pushing
-----------------------------------

Traffic Server comes with a Perl script for pushing, :program:`tspush`,
which can assist with understanding how to write scripts for pushing
content yourself.

Pinning Content in the Cache
============================

The *Cache Pinning Option* configures Traffic Server to keep certain
HTTP objects in the cache for a specified time. You can use this option
to ensure that the most popular objects are in cache when needed and to
prevent Traffic Server from deleting important objects. Traffic Server
observes ``Cache-Control`` headers and pins an object in the cache only
if it is indeed cacheable.

To set cache pinning rules:

#. Enable :ts:cv:`proxy.config.cache.permit.pinning` in :file:`records.config`::

        CONFIG proxy.config.cache.permit.pinning INT 1

#. Add a rule in :file:`cache.config` for each URL you want Traffic Server to
   pin in the cache. For example::

      url_regex=^https?://(www.)?apache.org/dev/ pin-in-cache=12h

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Caching HTTP Objects
====================

When Traffic Server receives a request for a web object that is not in
the cache, it retrieves the object from the origin server and serves it
to the client. At the same time, Traffic Server checks if the object is
cacheable before storing it in its cache to serve future requests.

Traffic Server responds to caching directives from clients and origin
servers, as well as directives you specify through configuration options
and files.

Client Directives
-----------------

By default, Traffic Server does not cache objects with the following
request headers:

-  ``Authorization``

-  ``Cache-Control: no-store``

-  ``Cache-Control: no-cache``

   To configure Traffic Server to ignore this request header, refer to
   `Configuring Traffic Server to Ignore Client no-cache Headers`_.

-  ``Cookie`` (for text objects)

   By default, Traffic Server caches objects served in response to
   requests that contain cookies (even if the object is text). You can
   configure Traffic Server to not cache cookied content of any type,
   cache all cookied content, or cache cookied content that is of image
   type only. For more information, refer to `Caching Cookied Objects`_.

Configuring Traffic Server to Ignore Client no-cache Headers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, Traffic Server strictly observes client
``Cache-Control: no-cache`` directives. If a requested object contains a
``no-cache`` header, then Traffic Server forwards the request to the
origin server even if it has a fresh copy in cache. You can configure
Traffic Server to ignore client ``no-cache`` directives such that it
ignores ``no-cache`` headers from client requests and serves the object
from its cache.

#. Edit :ts:cv:`proxy.config.http.cache.ignore_client_no_cache` in
   :file:`records.config`. ::

        CONFIG proxy.config.http.cache.ignore_client_no_cache INT 1

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Origin Server Directives
------------------------

=ron=
流量服务器支持HTTP ' '推送' '方法的内容传递。
使用HTTP ' ' PUSH ' '，你可以直接把内容发送到缓存中
没有客户机请求。

配置流量推送服务器
--------------------------------------------

在使用HTTP ' ' PUSH ' ' '将内容交付到缓存之前，您需要
必须配置流量服务器接受' ' PUSH ' '请求。

#。编辑:文件:“ip_allow。yaml '允许' PUSH '从适当的地址。

#。更新:ts:简历:“proxy.config.http。push_method_enabled”
:文件:“records.config”::

配置proxy.config.http。push_method_enabled INT 1

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

理解HTTP推
-----------------------

' ' PUSH ' '使用HTTP 1.1消息格式。PUSH的主体
request包含您想要的响应头和响应体
放入缓存中。下面是一个PUSH请求的例子:

将http://www.company.com HTTP / 1.0
内容长度:84

HTTP / 1.0 200 OK
内容类型:text / html
内容长度:17

< HTML >
一个
< / HTML >

. .重要的是::

你的' PUSH ' ' headers必须包含' ' Content-length ' '，其中的值
必须同时包含标题和正文的字节计数。该值不是可选的，
而不适当的值(过大或过小)则会导致不受欢迎的结果
的行为。

帮助管理推送的工具
-----------------------------------

Traffic Server自带一个Perl脚本，用于推送:program: ' tspush '，
哪些可以帮助理解如何编写推送脚本
内容你自己。

固定缓存中的内容
============================

缓存固定选项*配置流量服务器以保持一定
在指定的时间内缓存HTTP对象。您可以使用此选项
确保最流行的对象在需要时在缓存中
防止流量服务器删除重要对象。通信服务器
只在缓存中观察' ' cache - control ' '头和pin对象
如果它确实是可缓存的。

设置cache钉住规则。

#。启用:ts:简历:“proxy.config.cache.permit。把“:文件:“records.config”::

配置proxy.config.cache.permit。把INT 1

#。在:file: ' cache中添加规则。为您想要流量服务器的每个URL配置
插入缓存。例如::

url_regex = ^ https ?: / / (www) ? apache.org/dev/ pin-in-cache = 12 h

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

HTTP缓存对象
====================

当流量服务器接收到一个不存在的web对象请求时
缓存，它从源服务器检索对象并为其提供服务
给客户端。同时，流量服务器检查该对象是否为
在将其存储在其缓存中以服务于未来的请求之前可缓存。

流量服务器响应来自客户端和源端的缓存指令
服务器，以及通过配置选项指定的指令
和文件。

客户的指示
-----------------

缺省情况下，Traffic Server不会缓存下列对象
请求头信息:

——“授权”

——“cache - control:不是商店' '

——“cache - control: no - cache ' '

要配置流量服务器忽略此请求头，请参见
'配置流量服务器忽略客户端no-cache头' _。

- ' ' Cookie ' '(用于文本对象)

缺省情况下，流量服务器缓存响应对象
包含cookie的请求(即使对象是文本)。你可以
配置流量服务器不缓存任何类型的cookie内容，
缓存所有烹调的内容，或缓存图像烹调的内容
只有类型。要了解更多信息，请参阅' Caching Cookied Objects ' _。

配置流量服务器忽略客户端no-cache头
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

缺省情况下，Traffic Server对client严格遵守
“cache - control: no - cache”的指令。如果被请求的对象包含
' ' no-cache ' '头，然后流量服务器将请求转发到
原始服务器，即使它有一个新的副本在缓存中。您可以配置
流量服务器要忽略客户端的' ' no-cache ' '指令，这样它
忽略客户端请求中的' ' no-cache ' '头并服务对象
从它的缓存。

#。编辑:ts:简历:“proxy.config.http.cache。ignore_client_no_cache”
:文件:“records.config”。::

配置proxy.config.http.cache。ignore_client_no_cache INT 1

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

原始服务器指令
------------------------
=ron=



By default, Traffic Server does not cache objects with the following response
headers:

-  ``Cache-Control: no-store``

-  ``Cache-Control: private``

-  ``WWW-Authenticate``

   To configure Traffic Server to ignore ``WWW-Authenticate`` headers,
   refer to `Configuring Traffic Server to Ignore WWW-Authenticate Headers`_.

-  ``Set-Cookie``

-  ``Cache-Control: no-cache``

   To configure Traffic Server to ignore ``no-cache`` headers, refer to
   `Configuring Traffic Server to Ignore Server no-cache Headers`_.

-  ``Expires`` header with a value of 0 (zero) or a past date.

Configuring Traffic Server to Ignore Server no-cache Headers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, Traffic Server strictly observes ``Cache-Control: no-cache``
directives. A response from an origin server with a ``no-cache`` header
is not stored in the cache and any previous copy of the object in the
cache is removed. If you configure Traffic Server to ignore ``no-cache``
headers, then Traffic Server also ignores ``no-store`` headers. The
default behavior of observing ``no-cache`` directives is appropriate
in most cases.

To configure Traffic Server to ignore server ``no-cache`` headers:

#. Edit :ts:cv:`proxy.config.http.cache.ignore_server_no_cache` in
   :file:`records.config`. ::

        CONFIG proxy.config.http.cache.ignore_server_no_cache INT 1

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Configuring Traffic Server to Ignore WWW-Authenticate Headers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, Traffic Server does not cache objects that contain
``WWW-Authenticate`` response headers. The ``WWW-Authenticate`` header
contains authentication parameters the client uses when preparing the
authentication challenge response to an origin server.

When you configure Traffic Server to ignore origin server
``WWW-Authenticate`` headers, all objects with ``WWW-Authenticate``
headers are stored in the cache for future requests. However, the
default behavior of not caching objects with ``WWW-Authenticate``
headers is appropriate in most cases. Only configure Traffic Server to
ignore server ``WWW-Authenticate`` headers if you are knowledgeable
about HTTP 1.1.

To configure Traffic Server to ignore server ``WWW-Authenticate``
headers:

#. Edit :ts:cv:`proxy.config.http.cache.ignore_authentication` in
   :file:`records.config`. ::

        CONFIG proxy.config.http.cache.ignore_authentication INT 1

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Configuration Directives
------------------------

In addition to client and origin server directives, Traffic Server
responds to directives you specify through configuration options and
files.

You can configure Traffic Server to do the following:

-  Not cache any HTTP objects. Refer to `Disabling HTTP Object Caching`_.

-  Cache *dynamic content*. That is, objects with URLs that end in ``.asp`` or
   contain a question mark (``?``), semicolon (``;``), or ``cgi``. For more
   information, refer to `Caching Dynamic Content`_.

-  Cache objects served in response to the ``Cookie:`` header. Refer to
   `Caching Cookied Objects`_.

-  Observe ``never-cache`` rules in :file:`cache.config`.

Disabling HTTP Object Caching
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, Traffic Server caches all HTTP objects except those for
which you have set ``never-cache`` as :ref:`action rules <cache-config-format-action>`
in :file:`cache.config`. You can disable HTTP object caching so that all HTTP
objects are served directly from the origin server and never cached, as
detailed below.

To disable HTTP object caching manually:

#. Set :ts:cv:`proxy.config.http.cache.http` to ``0`` in :file:`records.config`. ::

        CONFIG proxy.config.http.cache.http INT 0

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Caching Dynamic Content
~~~~~~~~~~~~~~~~~~~~~~~

=ron=
默认情况下，Traffic Server不会缓存响应如下的对象
标题:

——“cache - control:不是商店' '

——“cache - control:私人' '

——“WWW-Authenticate ' '

要配置流量服务器忽略' ' WWW-Authenticate ' '报头，
请参考'配置流量服务器忽略WWW-Authenticate报头' _。

”——“set - cookie””

——“cache - control: no - cache ' '

要配置流量服务器忽略' ' no-cache ' '报头，请参见
'配置流量服务器忽略服务器no-cache头' _。

- ' ' Expires ' '头的值为0(零)或过去的日期。

配置流量服务器忽略Server no-cache头
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

缺省情况下，Traffic Server严格遵守' ' Cache-Control: no-cache ' '
指令。带有' ' no-cache ' '头的源服务器响应
没有存储在缓存和对象的任何以前的副本
删除缓存。如果您配置流量服务器忽略' ' no-cache ' '
头，然后流量服务器也忽略' ' no-store ' '头。的
观察' ' no-cache ' '指令的默认行为是合适的
在大多数情况下。

配置流量服务器忽略服务器' ' no-cache ' '报头:

#。编辑:ts:简历:“proxy.config.http.cache。ignore_server_no_cache”
:文件:“records.config”。::

配置proxy.config.http.cache。ignore_server_no_cache INT 1

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

配置流量服务器忽略WWW-Authenticate报头
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

默认情况下，流量服务器不缓存包含
“WWW-Authenticate“响应标头。“WWW-Authenticate的头
包含客户机在准备时使用的身份验证参数
对源服务器的身份验证询问响应。

配置“流量服务器”忽略“源服务器”时
' ' WWW-Authenticate ' '头文件，所有带有' ' WWW-Authenticate ' '的对象
报头存储在缓存中，以备将来的请求使用。然而,
不使用“WWW-Authenticate”缓存对象的默认行为
大多数情况下，headers是合适的。只配置流量服务器为
如果您了解情况，请忽略服务器的“WWW-Authenticate”报头
HTTP 1.1。

配置流量服务器忽略服务器“WWW-Authenticate”
标题:

#。编辑:ts:简历:“proxy.config.http.cache。ignore_authentication”
:文件:“records.config”。::

配置proxy.config.http.cache。ignore_authentication INT 1

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

配置指令
------------------------

除了客户端和源服务器指令外，流量服务器
响应通过配置选项指定的指令
文件。

通过配置流量服务器，可以实现以下功能:

—不缓存任何HTTP对象。参考'禁用HTTP对象缓存' _。

—缓存*动态内容*。也就是url以' '结尾的对象。asp”或
包含一个问号  (``?``), 分号  (``;``), ”或“cgi””。更多的
信息，请参阅'缓存动态内容' _。

-响应' ' Cookie: ' '报头的缓存对象。指
对象缓存饼_。

-遵循:file: ' cache.config '中的' ' never-cache ' '规则。

禁用HTTP对象缓存
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

默认情况下，流量服务器缓存所有HTTP对象，除了那些
你已经设置了' ' ' never-cache ' ' as:ref: ' action rules <cache-config-format-action> '</cache-config-format-action>
:文件:“cache.config”。您可以禁用HTTP对象缓存，以便所有的HTTP
对象直接从源服务器提供，从不缓存，例如
详细的下面。

手动禁用HTTP对象缓存:

#。设置:ts:简历:“proxy.config.http.cache。http '到' 0 ' '在:file: ' records.config '。::

配置proxy.config.http.cache。http INT 0

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

缓存动态内容
~~~~~~~~~~~~~~~~~~~~~~~
=ron=


A URL is considered dynamic if it ends in ``.asp`` or contains a
question mark (``?``), a semicolon (``;``), or ``cgi``. By
default, Traffic Server caches dynamic content. You can configure the
system to ignore dynamic looking content, although this is recommended
only if the content is truly dynamic, but fails to advertise so with
appropriate ``Cache-Control`` headers.

To configure Traffic Server's cache behaviour in regard to dynamic
content:

#. Edit :ts:cv:`proxy.config.http.cache.cache_urls_that_look_dynamic` in
   :file:`records.config`. To disable caching, set the variable to ``0``,
   and to explicitly permit caching use ``1``. ::

        CONFIG proxy.config.http.cache.cache_urls_that_look_dynamic INT 0

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Caching Cookied Objects
~~~~~~~~~~~~~~~~~~~~~~~

.. XXX This should be extended to xml as well!

By default, Traffic Server caches objects served in response to requests
that contain cookies. This is true for all types of objects including
text. Traffic Server does not cache cookied text content because object
headers are stored along with the object, and personalized cookie header
values could be saved with the object. With non-text objects, it is
unlikely that personalized headers are delivered or used.

You can reconfigure Traffic Server to:

-  Not cache cookied content of any type.

-  Cache cookied content that is of image type only.

-  Cache all cookied content regardless of type.

To configure how Traffic Server caches cookied content:

#. Edit :ts:cv:`proxy.config.http.cache.cache_responses_to_cookies` in
   :file:`records.config`.

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Forcing Object Caching
======================

You can force Traffic Server to cache specific URLs (including dynamic
URLs) for a specified duration, regardless of ``Cache-Control`` response
headers.

To force document caching:

#. Add a rule for each URL you want Traffic Server to pin to the cache
   :file:`cache.config`::

       url_regex=^https?://(www.)?apache.org/dev/ ttl-in-cache=6h

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

Caching HTTP Alternates
=======================

Some origin servers answer requests to the same URL with a variety of
objects. The content of these objects can vary widely, according to
whether a server delivers content for different languages, targets
different browsers with different presentation styles, or provides
different document formats (HTML, XML). Different versions of the same
object are termed *alternates* and are cached by Traffic Server based
on ``Vary`` response headers. You can also limit the number of
alternate versions of an object allowed in the cache.

Limiting the Number of Alternates for an Object
-----------------------------------------------

You can limit the number of alternates Traffic Server can cache per
object (the default is 3).

.. important::

   Large numbers of alternates can affect Traffic Server
   cache performance because all alternates have the same URL. Although
   Traffic Server can look up the URL in the index very quickly, it must
   scan sequentially through available alternates in the object store.

To alter the limit on the number of alternates:

#. Edit :ts:cv:`proxy.config.cache.limits.http.max_alts` in :file:`records.config`. ::

    CONFIG proxy.config.cache.limits.http.max_alts INT 5

#. Run the command :option:`traffic_ctl config reload` to apply the configuration changes.

.. _transaction-buffering-control:

Using Transaction Buffering Control
===================================

=ron=
以' '结尾的URL被认为是动态的。asp ' '或包含一个
问号  (``?``), 一个分号  (``;``), ”或“cgi””。通过
默认情况下，流量服务器缓存动态内容。您可以配置
系统将忽略动态外观的内容，尽管建议这样做
只有当内容真正是动态的，但却不能这样做广告
适当的“cache - control‘头。

将流量服务器的缓存行为配置为动态的
内容:

#。编辑:ts:简历:“proxy.config.http.cache。cache_urls_that_look_dynamic”
:文件:“records.config”。要禁用缓存，将变量设置为' ' 0 ' '，
为了显式地允许缓存使用' ' 1 ' '。::

配置proxy.config.http.cache。cache_urls_that_look_dynamic INT 0

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

对象缓存饼
~~~~~~~~~~~~~~~~~~~~~~~

. .这也应该扩展到xml !

默认情况下，流量服务器缓存响应请求的对象
包含饼干。这适用于所有类型的对象，包括
文本。流量服务器不缓存cookied文本内容，因为对象
标头与对象和个性化的cookie标头一起存储
值可以保存在对象中。对于非文本对象，则是这样
不太可能交付或使用个性化的标头。

您可以重新配置流量服务器:

不缓存任何类型的cookie内容。

—仅缓存图像类型的cookie内容。

-缓存所有cookied内容，无论类型。

配置流量服务器如何缓存cookie内容:

#。编辑:ts:简历:“proxy.config.http.cache。cache_responses_to_cookies”
:文件:“records.config”。

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

迫使对象缓存
======================

您可以强制Traffic Server缓存特定的url(包括动态的)
url)，不管' ' Cache-Control ' '响应如何
头。

强制文档缓存:

#。为您希望Traffic Server标记到缓存中的每个URL添加一条规则
:文件:“cache.config”::

url_regex = ^ https ?: / / (www) ? apache.org/dev/ ttl-in-cache = 6 h

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

缓存HTTP交替
=======================

一些源服务器用各种不同的方式来响应对同一个URL的请求
对象。这些对象的内容可能会有很大的不同
服务器是否为不同的语言、目标交付内容
不同的浏览器具有不同的表示样式，或提供
不同的文档格式(HTML, XML)。相同的不同版本
对象被称为*替代*，由流量服务器缓存
对' ' Vary ' '响应头。你也可以限制数量
缓存中允许的对象的替代版本。

限制对象的备选项数量
-----------------------------------------------

您可以限制每个流量服务器可以缓存的备用流量的数量
对象(默认为3)。

. .重要的是::

大量的备选项会影响流量服务器
缓存性能，因为所有备选选项都有相同的URL。虽然
流量服务器可以在索引中快速查找URL，这是必须的
按顺序扫描对象存储中的可用替换。

改变候补人数的限制:

#。编辑:ts:简历:“proxy.config.cache.limits.http。max_alts”:文件:“records.config”。::

配置proxy.config.cache.limits.http。max_alts INT 5

#。执行option: ' traffic_ctl config reload '命令应用配置更改。

. ._transaction-buffering-control:

使用事务缓冲控制
===================================
=ron=



By default, I/O operations are run at full speed, as fast as either Traffic
Server, the network, or the cache can support. This can be problematic for
large objects if the client side connection is significantly slower. In such
cases the content will be buffered in ram while waiting to be sent to the
client. This could potentially also happen for ``POST`` requests if the client
connection is fast and the origin server connection slow. If very large objects
are being used this can cause the memory usage of Traffic Server to become
`very large <https://issues.apache.org/jira/browse/TS-1496>`_.

This problem can be ameliorated by controlling the amount of buffer space used
by a transaction. A high water and low water mark are set in terms of bytes
used by the transaction. If the buffer space in use exceeds the high water
mark, the connection is throttled to prevent additional external data from
arriving. Internal operations continue to proceed at full speed until the
buffer space in use drops below the low water mark and external data I/O is
re-enabled.

Although this is intended primarily to limit the memory usage of Traffic Server
it can also serve as a crude rate limiter by setting a buffer limit and then
throttling the client side connection either externally or via a transform.
This will cause the connection to the origin server to be limited to roughly
the client side connection speed.

Traffic Server does network I/O in large chunks (32K or so) and therefore the
granularity of transaction buffering control is limited to a similar precision.

The buffer size calculations include all elements in the transaction, including
any buffers associated with :ref:`transform plugins <developer-plugins-http-transformations>`.

Transaction buffering control can be enabled globally by using configuration
variables or by :c:func:`TSHttpTxnConfigIntSet` in a plugin.

================= ================================================== =======================================================
Value             Variable                                           :c:func:`TSHttpTxnConfigIntSet` key
================= ================================================== =======================================================
Enable buffering  :ts:cv:`proxy.config.http.flow_control.enabled`    :c:member:`TS_CONFIG_HTTP_FLOW_CONTROL_ENABLED`
Set high water    :ts:cv:`proxy.config.http.flow_control.high_water` :c:member:`TS_CONFIG_HTTP_FLOW_CONTROL_HIGH_WATER_MARK`
Set low water     :ts:cv:`proxy.config.http.flow_control.low_water`  :c:member:`TS_CONFIG_HTTP_FLOW_CONTROL_LOW_WATER_MARK`
================= ================================================== =======================================================

Be careful to always have the low water mark equal or less than the high water
mark. If you set only one, the other will be set to the same value.

If using :c:func:`TSHttpTxnConfigIntSet`, it must be called no later than
:c:data:`TS_HTTP_READ_RESPONSE_HDR_HOOK`.

.. _admin-configuration-reducing-origin-requests:

Reducing Origin Server Requests (Avoiding the Thundering Herd)
==============================================================

When an object can not be served from cache, the request will be proxied to the
origin server. For a popular object, this can result in many near simultaneous
requests to the origin server, potentially overwhelming it or associated
resources. There are several features in Traffic Server that can be used to
avoid this scenario.

.. _admin-config-read-while-writer:

Read While Writer
-----------------

When Traffic Server goes to fetch something from origin, and upon receiving
the response, any number of clients can be allowed to start serving the
partially filled cache object once background_fill_completed_threshold % of the
object has been received.

While some other HTTP proxies permit clients to begin reading the response
immediately upon the proxy receiving data from the origin server, ATS does not
begin allowing clients to read until after the complete HTTP response headers
have been read and processed. This is a side-effect of ATS making no
distinction between a cache refresh and a cold cache, which prevents knowing
whether a response is going to be cacheable.

As non-cacheable responses from an origin server are generally due to that
content being unique to different client requests, ATS will not enable
read-while-writer functionality until it has determined that it will be able
to cache the object.

The following settings must be made in :file:`records.config` to enable
read-while-writer functionality in ATS::

    CONFIG proxy.config.cache.enable_read_while_writer INT 1
    CONFIG proxy.config.http.background_fill_active_timeout INT 0
    CONFIG proxy.config.http.background_fill_completed_threshold FLOAT 0.000000
    CONFIG proxy.config.cache.max_doc_size INT 0

=ron=
默认情况下，I/O操作以全速运行，速度与任一流量一样快
服务器、网络或缓存都可以支持。这可能会有问题
大对象，如果客户端连接明显较慢。在这样的
在等待被发送到的情况下，内容将被缓冲在ram中
客户端。这也可能发生在' ' POST ' '请求，如果客户端
连接速度快，源服务器连接速度慢。如果是非常大的物体
正在使用这是否会导致服务器的内存使用流量变大
“非常大的1496年< https://issues.apache.org/jira/browse/ts > _。

这个问题可以通过控制使用的缓冲区空间来改善
通过一个事务。以字节为单位设置高水位和低水位标记
由事务使用。如果正在使用的缓冲区空间超过高水位
标记，连接被限制，以防止额外的外部数据
到达。内部行动继续全速进行，直到
正在使用的缓冲区空间低于低水位标志，外部数据I/O是
重新启用。

尽管这主要是为了限制流量服务器的内存使用
它也可以作为一个粗略的速率限制器，通过设置缓冲限制，然后
从外部或通过转换限制客户端连接。
这将导致到源服务器的连接被粗略地限制为
客户端连接速度。

流量服务器以大块(32K左右)进行网络I/O，因此
事务缓冲控制的粒度也受到类似精度的限制。

缓冲区大小计算包括事务中的所有元素，包括
任何与:ref: ' transform plugins <developer-plugins-http- transforms=""> '相关的缓冲区。</developer-plugins-http->

事务缓冲控制可以通过使用配置全局启用
变量或者在插件中使用:c:func: ' TSHttpTxnConfigIntSet '。

================= ================================================== =======================================================
值变量:c:func: ' TSHttpTxnConfigIntSet '键
================= ================================================== =======================================================
使缓冲:ts:简历:“proxy.config.http.flow_control。启用”:c:成员:“TS_CONFIG_HTTP_FLOW_CONTROL_ENABLED”
设置高水位:ts:cv: ' proxy.config.http.flow_control. 'high_water”:c:成员:“TS_CONFIG_HTTP_FLOW_CONTROL_HIGH_WATER_MARK”
设置低水位:ts:cv:`proxy.config.http.flow_control。low_water”:c:成员:“TS_CONFIG_HTTP_FLOW_CONTROL_LOW_WATER_MARK”
================= ================================================== =======================================================

注意要使低水位标志等于或小于高水位标志
马克。如果只设置其中一个，另一个将被设置为相同的值。

如果使用:c:func: ' TSHttpTxnConfigIntSet '，它必须在
c:数据:“TS_HTTP_READ_RESPONSE_HDR_HOOK”。

. ._admin-configuration-reducing-origin-requests:

减少源服务器请求(避免蜂拥而至)
==============================================================

当不能从缓存中提供对象时，请求将被代理到
原始服务器。对于一个流行的对象，这可能导致许多几乎同时发生
请求源服务器，潜在的压倒它或关联
资源。流量服务器中有几个特性可以用于
避免这种情况。

. ._admin-config-read-while-writer:

读当作家
-----------------

当流量服务器去取一些东西从原点，并在接收
响应时，允许任意数量的客户端开始服务
部分填充的缓存对象，一旦background_fill_completed_threshold %的
对象已被接收。

而其他一些HTTP代理允许客户机开始读取响应
当代理从源服务器接收数据时，ATS不接收
开始允许客户端读取，直到完成HTTP响应头
已被读取和处理。这是ATS的副作用
缓存刷新和冷缓存之间的区别，这使我们无法了解
响应是否可缓存。

因为来自源服务器的不可缓存响应通常是由于这个原因
对于不同的客户端请求，内容是唯一的，ATS将不启用
边读边写功能，直到它确定它能够
缓存对象。

以下设置必须在:file: ' records中进行。配置”,使
ATS的边读边写功能:

配置proxy.config.cache。enable_read_while_writer INT 1
配置proxy.config.http。background_fill_active_timeout INT 0
配置proxy.config.http。background_fill_completed_threshold浮动0.000000
配置proxy.config.cache。max_doc_size INT 0
=ron=


All four configurations are required, for the following reasons:

-  :ts:cv:`proxy.config.cache.enable_read_while_writer` being set to ``1`` turns
   the feature on, as it is off (``0``) by default.

.. _background_fill:

-  The background fill feature (both
   :ts:cv:`proxy.config.http.background_fill_active_timeout` and
   :ts:cv:`proxy.config.http.background_fill_completed_threshold`) should be
   allowed to kick in for every possible request. This is necessary in the event
   the writer (the first client session to request the object, which triggered
   ATS to contact the origin server) goes away. Another client session needs to
   take over the writer.

   As such, you should set the background fill timeouts and threshold to zero;
   this assures they never time out and are always allowed to kick in.

-  The :ts:cv:`proxy.config.cache.max_doc_size` should be unlimited (set to 0),
   since the object size may be unknown, and going over this limit would cause
   a disconnect on the objects being served.

Once these are enabled, you have something that is very close, but not quite
the same, to Squid's Collapsed Forwarding.

In addition to the above settings, the settings :ts:cv:`proxy.config.cache.read_while_writer.max_retries`
and :ts:cv:`proxy.config.cache.read_while_writer_retry.delay` allow to control the number
of retries TS attempts to trigger read-while-writer until the download of first fragment
of the object is completed::

    CONFIG proxy.config.cache.read_while_writer.max_retries INT 10

    CONFIG proxy.config.cache.read_while_writer_retry.delay INT 50


Open Read Retry Timeout
-----------------------

The open read retry configurations attempt to reduce the number of concurrent
requests to the origin for a given object. While an object is being fetched
from the origin server, subsequent requests would wait
:ts:cv:`proxy.config.http.cache.open_read_retry_time` milliseconds before
checking if the object can be served from cache. If the object is still being
fetched, the subsequent requests will retry
:ts:cv:`proxy.config.http.cache.max_open_read_retries` times. Thus, subsequent
requests may wait a total of (``max_open_read_retries`` x ``open_read_retry_time``)
milliseconds before establishing an origin connection of its own. For instance,
if they are set to ``5`` and ``10`` respectively, connections will wait up to
50ms for a response to come back from origin from a previous request, until
this request is allowed through.

.. important::

    These settings are inappropriate when objects are uncacheable. In those
    cases, requests for an object effectively become serialized. The subsequent
    requests would await at least ``open_read_retry_time`` milliseconds before
    being proxied to the origin.

It is advisable that this setting be used in conjunction with `Read While Writer`_
for big (those that take longer than (``max_open_read_retries`` x
``open_read_retry_time``) milliseconds to transfer) cacheable objects. Without
the read-while-writer settings enabled, while the initial fetch is ongoing, not
only would subsequent requests be delayed by the maximum time, but also, those
requests would result in unnecessary requests to the origin server.

Since ATS now supports setting these settings per-request or remap rule, you
can configure this to be suitable for your setup much more easily.

The configurations are (with defaults)::

    CONFIG proxy.config.http.cache.max_open_read_retries INT -1
    CONFIG proxy.config.http.cache.open_read_retry_time INT 10

The defaults are such that the feature is disabled and every connection is
allowed to go to origin without artificial delay. When enabled, you will try
``max_open_read_retries`` times, each with an ``open_read_retry_time`` timeout.

Open Write Fail Action
----------------------

In addition to the open read retry settings TS supports a new setting
:ts:cv:`proxy.config.http.cache.open_write_fail_action` that allows to further
reduce multiple concurrent requests hitting the origin for the same object by
either returning a stale copy, in case of hit-stale or an error in case of cache
miss for all but one of the requests.

=ron=
所有四种配置都是必需的，原因如下:

-: ts:简历:“proxy.config.cache。enable_read_while_writer设置为“1”回合
这个特性是开启的，因为它默认是关闭的(' ' 0 ' ')。

. ._background_fill:

-背景填充功能(两者都有
ts:简历:“proxy.config.http。background_fill_active_timeout”和
ts:简历:“proxy.config.http.background_fill_completed_threshold”)
允许对每一个可能的请求给予帮助。在这种情况下这是必要的
写入器(请求对象的第一个客户端会话，它触发了
联系源服务器的ATS)消失。另一个客户端会话需要
接管作家。

因此，您应该将背景填充超时和阈值设置为零;
这保证了他们永远不会停下来，而且总是允许他们开始工作。

——:ts:简历:“proxy.config.cache。max_doc_size应该是无限的(设置为0)，
因为对象大小可能是未知的，超过这个限制会导致
正在服务的对象断开连接。

一旦这些被启用，你会得到一些非常接近的东西，但不完全是
同样的，对于鱿鱼的坍塌前进。

除了上述设置，设置:ts:cv: ' proxy.config.cache.read_while_writer.max_retries '
和:ts:cv: ' proxy.config.cache.read_while_writer_retry.delay '允许控制数字
TS尝试触发读时写入器，直到下载第一个片段
完成对象的::

配置proxy.config.cache.read_while_writer。max_retries INT 10

CONFIG proxy.config.cache.read_while_writer_retry.delay INT 50


打开读重试超时
-----------------------

open read retry配置试图减少并发数
对给定对象的源请求。当对象被获取时
来自源服务器的后续请求将等待
ts:简历:“proxy.config.http.cache。open_read_retry_time的毫秒之前
检查是否可以从缓存中提供对象。如果对象仍然存在
获取后，后续请求将重试
ts:简历:“proxy.config.http.cache。max_open_read_retries”时代。因此,随后的
请求可能会等待(' max_open_read_retries ' ' x ' open_read_retry_time ' ')
在建立自己的起源连接之前的毫秒数。例如,
如果它们分别设置为' 5 '和' 10 '，连接将等待到
从上一个请求返回响应的时间为50ms，直到
这个请求被允许通过。

. .重要的是::

当对象不可缓存时，这些设置是不合适的。在那些
在这种情况下，对对象的请求有效地序列化了。随后的
请求将在至少毫秒之前等待' ' open_read_retry_time ' '
被代理到原点。

建议将此设置与' Read While Writer ' _一起使用
max_open_read_retries`` x . max_open_read_retries`` x . max_open_read_retries``
' open_read_retry_time ')传输可缓存对象的毫秒数。没有
当初始读取正在进行时，读写设置启用，而不是
只有后续的请求才会被延迟到最大时间，这些请求也一样
请求将导致向源服务器发出不必要的请求。

由于ATS现在支持根据请求或重新映射规则设置这些设置，您可以
可以更容易地将其配置为适合您的设置。

配置是(默认)::

配置proxy.config.http.cache。max_open_read_retries INT 1
配置proxy.config.http.cache。open_read_retry_time INT 10

默认情况下，该特性是禁用的，每个连接都是禁用的
允许在没有人为延误的情况下到达原点。当启用时，您将尝试
max_open_read_retries次数，每个都有一个open_read_retry_time超时。

打开写失败操作
----------------------

除了“打开读取重试”设置外，TS还支持一个新设置
ts:简历:“proxy.config.http.cache。open_write_fail_action '允许进一步
减少击中同一对象原点的多个并发请求
要么返回过期副本(在hit-stale情况下)，要么在缓存时返回错误
除了一项要求，其他要求都没有满足。
=ron=

