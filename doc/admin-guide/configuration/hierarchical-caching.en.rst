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

.. _admin-hierarchical-caching:

Hierarchical Caching
********************

.. toctree::
   :maxdepth: 2

Understanding Cache Hierarchies
===============================

A cache hierarchy consists of cache levels that communicate with each
other. Traffic Server supports several types of cache hierarchies. All
cache hierarchies recognize the concept of *parent* and *child*. A
parent cache is a cache higher up in the hierarchy, to which Traffic
Server can forward requests. A child cache is a cache for which Traffic
Server is a parent.

Traffic Server supports the following hierarchical caching options:

Parent Caching
==============

If a Traffic Server node cannot find a requested object in its cache,
then it searches a parent cache (which itself can search other caches)
before finally retrieving the object from the origin server. You can
configure a Traffic Server node to use multiple parent caches so that
if one parent is unavailable, the other parent caches will be checked in turn
until either the request is serviced properly or no further parent caches are
available and the origin server is contacted. This is called `Parent Failover`_.
Traffic Server supports parent caching for both HTTP and HTTPS requests.

If you do not want all requests to go to the parent cache, then simply configure
Traffic Server to route certain requests (such as requests containing specific
URLs) directly to the origin server. This may be achieved by setting parent
proxy rules in :file:`parent.config`.

The figure below illustrates a simple cache hierarchy with a Traffic
Server node configured to use a parent cache. In the following scenario,
a client sends a request to a Traffic Server node that is a child in the
cache hierarchy (because it's configured to forward missed requests to a
parent cache). The request is a cache miss, so Traffic Server then
forwards the request to the parent cache where it is a cache hit. The
parent sends a copy of the content to the Traffic Server, where it is
cached and then served to the client. Future requests for this content
can now be served directly from the Traffic Server cache (until the data
is stale or expired).

.. figure:: /static/images/admin/cachehrc.jpg
   :align: center
   :alt: Parent caching

   Parent caching

If the request is a cache miss on the parent, then the parent retrieves the
content from the origin server (or from another cache, depending on the parent's
configuration). The parent caches the content and then sends a copy to Traffic
Server (its child), where it is cached and served to the client.

Parent Selection Policies
-------------------------

There are several parent selection policies available to the Traffic Server child
node.

    - Consistent Hash. The child node chooses a specific parent for each URI. This effectively
      makes the parent's cache size the sum total of each of the individual parent cache
      sizes.
    - Round Robin. The child node cycles through the parents. The child can select the parent
      based on the client IP ("true"), or in a strict cycling ("strict").
    - (Unnamed). The child node chooses the first live parent listed. There are two variants to this
      strategy.  When the strategy is set to "false," the child will use the first listed parent
      (for clarity called p1) until it is marked down, when the child will switch to the second
      listed parent (p2). Then, when the p1 is retested and found live, the child
      will restart using p1. When the selection strategy is set to "latched," the child will use
      p1 until it is marked down, when it will switch to p2. When p1 is retested and found live,
      the child will continue using p2 until it is marked down.

Interaction with Remap.config
-----------------------------

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

. ._admin-hierarchical-caching:

分层缓存
********************

. .toctree::
: maxdepth: 2

理解缓存层次结构
===============================

缓存层次结构由与每个缓存层通信的缓存层组成
其他。Traffic Server支持几种类型的缓存层次结构。所有
缓存层次结构可以识别*父*和*子*的概念。一个
父缓存是层次结构中较高的缓存，流量要到达该缓存
服务器可以转发请求。子缓存是用于流量的缓存
Server是父节点。

Traffic Server支持以下分级缓存选项:

父母缓存
==============

如果流量服务器节点在其缓存中找不到被请求的对象，
然后搜索父缓存(父缓存本身也可以搜索其他缓存)
在最后从源服务器检索对象之前。你可以
配置流量服务器节点以使用多个父缓存，以便
如果一个父缓存不可用，则会依次检查另一个父缓存
直到请求得到正确的服务或不再有父缓存
可用，并与源服务器联系。这被称为'父故障转移' _。
流量服务器支持HTTP和HTTPS请求的父缓存。

如果您不希望所有请求都转到父缓存，那么只需进行配置
流量服务器路由某些请求(例如请求包含特定的
url)直接指向源服务器。这可以通过设置parent来实现
代理规则在:file: ' parent.config '。

下图展示了一个带有流量的简单缓存层次结构
配置为使用父缓存的服务器节点。在下面的场景中，
客户端向通信服务器节点发送请求，该节点是
缓存层次结构(因为它被配置为将错过的请求转发到
父缓存)。请求是缓存错过，所以流量服务器
将请求转发到父缓存，该请求是缓存命中。的
父服务器向流量服务器发送内容的副本
缓存，然后服务给客户机。对该内容的未来请求
现在可以直接从流量服务器缓存服务(直到数据
过期的)。

. .图::/ admin / cachehrc.jpg /静态图像
对齐:中心
: alt:父母缓存

父母缓存

如果请求是父节点的缓存缺失，则父节点检索
来自源服务器的内容(或者来自另一个缓存，取决于父服务器的缓存
配置)。父进程缓存内容，然后向通信流发送副本
服务器(它的子服务器)，在那里它被缓存并服务给客户机。

父母的选择策略
-------------------------

流量服务器子服务器有几个可用的父选择策略
节点。

- - - - - -一致的哈希。子节点为每个URI选择一个特定的父节点。这有效地
使父缓存大小为每个单独父缓存的总和
大小。
——循环。子节点循环遍历父节点。子节点可以选择父节点
基于客户端IP ("true")，或在严格循环("strict")。
——(匿名)。子节点选择列出的第一个活动父节点。这有两种变体
策略。当策略设置为“false”时，子节点将使用列出的第一个父节点
(为了清晰起见，称为p1)直到它被标记下来，这时子进程将切换到第二个进程
上市母公司(p2)。然后，当p1被重新测试发现是活的，孩子
将使用p1重新启动。当选择策略设置为“latched”时，孩子将使用
p1直到它被标记下来，然后它会切换到p2。当p1被重新测试发现是活的，
孩子会继续使用p2，直到它的分数降低。

与Remap.config互动
-----------------------------
=ron=



If remap rules are required (:ts:cv:`proxy.config.reverse_proxy.enabled`),
when a request comes in to a child node, its :file:`remap.config` is evaluated before
parent selection. This means that the client request is translated according to the
remap rule, and therefore, any parent selection should be made against the remapped
host name. This is true regardless of pristine host headers
(:ts:cv:`proxy.config.url_remap.pristine_host_hdr`) being enabled or not. The parent node
will receive the translated request (and thus needs to be configured to accept it).

:file:`remap.config` now also allows an alternative configuration that supports all the
**Parent Selection** policies and failover mentioned here using a new :file:`remap.config` tag,
**@strategy**. This eliminates the need for a second lookup against the remapped host name
required when using :file:`parent.config`.  See using NextHop strategies with :file:`remap.config`,
:doc:`../../admin-guide/files/strategies.yaml.en`

Example
~~~~~~~
The client makes a request to Traffic Server for http://example.com. The origin server
for the request is http://origin.example.com; the parent node is ``parent1.example.com``,
and the child node is configured as a reverse proxy.

If the child's :file:`remap.config` contains

``map http://example.com http://origin.example.com``

with the child's :file:`parent.config` containing

``dest_domain=origin.example.com method=get parent="parent1.example.com:80`` )

and parent cache (parent1.example.com) would need to have a :file:`remap.config`
line similar to

``map http://origin.example.com http://origin.example.com``

With this example, if parent1.example.com is down, the child node would automatically
directly contact the ``origin.example.com`` on a cache miss.


Parent Failover
---------------

Traffic Server supports use of several parent caches. This ensures that
if one parent cache is not available, another parent cache can service
client requests.

When you configure your Traffic Server to use more than one parent
cache, Traffic Server detects when a parent is not available and sends
missed requests to another parent cache. If you specify more than two
parent caches, then the order in which the parent caches are queried
depends upon the parent proxy rules configured in the :file:`parent.config`
configuration file. By default, the parent caches are queried in the
order they are listed in the configuration file.

.. _configuring-traffic-server-to-use-a-parent-cache:

Configuring Traffic Server to Use a Parent Cache
------------------------------------------------

To configure Traffic Server to use one or more parent caches, you must perform
the configuration adjustments detailed below.

.. note::

    You need to configure the child cache only. Assuming the parent nodes are
    configured to serve the child's origin server, no additional configuration is
    needed for the nodes acting as Traffic Server parent caches.

#. Identify the parent cache you want to use to service missed requests. To
   use parent failover, you must identify more than one parent cache so that
   when a parent cache is unavailable, requests are sent to another parent
   cache.

#. Edit :file:`parent.config` to set parent proxy rules which will specify the
   parent cache to which you want missed requests to be forwarded.  Or as an
   alternative to :file:`parent.config`, edit :file:`strategies.yaml` to
   specify next hop parent proxy rules and hosts.  Then in :file:`remap.config`
   use the **@strategy** tag to select the next hop parent proxy rules. See
   :doc:`../../admin-guide/files/strategies.yaml.en`

The following example configures Traffic Server to route all requests
containing the regular expression ``politics`` and the path
``/viewpoint`` directly to the origin server (bypassing any parent
hierarchies): ::

    url_regex=politics prefix=/viewpoint go_direct=true

The following example configures Traffic Server to direct all missed
requests with URLs beginning with ``http://host1`` to the parent cache
``parent1``. If ``parent1`` cannot serve the requests, then requests are
forwarded to ``parent2``. Because ``round-robin=true``, Traffic Server
goes through the parent cache list in a round-robin based on client IP
address.::

    dest_host=host1 scheme=http parent="parent1;parent2" round-robin=strict

Run the command :option:`traffic_ctl config reload` to apply the configuration changes.


=ron=
如果需要重映射规则(:ts:cv: ' proxy.config.reverse_proxy.enabled ')，
当一个请求进入到一个子节点时，它的:file: ' remap。config '之前被评估过
父母的选择。这意味着客户端请求根据
重映射规则，因此，任何父选择都应该针对重映射
主机名。无论主机头是否纯净，这都是正确的
(:ts:cv: ' proxy.config.url_remap.pristine_host_hdr ')是否启用。父节点
将接收转换后的请求(因此需要配置为接受请求)。

:文件:“重新映射。config '现在也允许一个替代配置来支持所有的
**父选择**这里提到的策略和故障转移使用新的:file: ' remap。配置”标签,
* * @strategy * *。这样就不需要对映射的主机名进行二次查找
当使用:file: ' parent.config '时需要。参见:file: ' remap.config '使用下一跳策略，
:医生:“. . / . . / admin-guide /文件/ strategies.yaml.en”

例子
~ ~ ~ ~ ~ ~ ~
客户端向流量服务器请求http://example.com。源服务器
对于请求为http://origin.example.com;父节点是' parent1.example.com ' '，
子节点被配置为反向代理。

如果孩子的:file: ' remap. '配置的包含

“地图http://example.com http://origin.example.com ' '

用孩子的:file: ' parent。配置的包含

dest_domain=origin.example.com method=get parent="parent1.example.com:80 ' ")

而父缓存(parent1.example.com)需要有:file: ' remap.config '
类似于行

“地图http://origin.example.com http://origin.example.com ' '

在这个示例中，如果parent1.example.com关闭，则子节点将自动关闭
如果缓存失败，直接联系' ' origin.example.com ' '。


父母故障转移
---------------

流量服务器支持使用多个父缓存。这将确保
如果一个父缓存不可用，另一个父缓存可以服务
客户机请求。

当您将流量服务器配置为使用多个父服务器时
缓存，流量服务器检测到父服务器不可用时发送
对另一个父缓存的错过请求。如果指定两个以上
父缓存，然后是查询父缓存的顺序
取决于:file: ' parent.config '中配置的父代理规则
配置文件。默认情况下，查询父缓存
它们在配置文件中列出的顺序。

. ._configuring-traffic-server-to-use-a-parent-cache:

配置流量服务器以使用父缓存
------------------------------------------------

要配置流量服务器以使用一个或多个父缓存，您必须执行
下面详细介绍了配置调整。

. .注意::

您只需要配置子缓存。假设父节点是
配置为服务于子服务器的源服务器，不需要其他配置
作为流量服务器父缓存的节点所需要的。

#。确定要用于为错过的请求提供服务的父缓存。来
使用父故障转移，您必须标识多个父缓存，以便
当一个父缓存不可用时，请求被发送到另一个父缓存
缓存。

#。编辑:文件:“父母。设置父代理规则，该规则将指定
希望将错过的请求转发到的父缓存。或作为一个
替代品:文件:父母。配置”,编辑:文件:“策略。yaml”
指定下一跳父代理规则和主机。然后:文件:“remap.config”
使用**@strategy**标签选择下一跳父代理规则。看到
:医生:“. . / . . / admin-guide /文件/ strategies.yaml.en”

下面的示例配置流量服务器来路由所有请求
包含正则表达式“politics”和路径
' ' /视点' '直接指向源服务器(绕过任何父服务器)
层次结构):::

url_regex = =政治前缀/观点go_direct = true

下面的示例配置流量服务器来引导所有错过的流量
url以' ' http://host1 ' '开头的请求到父缓存
' ' parent1 ' '。如果' ' parent1 ' '不能服务请求，那么请求将
转发到“parent2“……。因为' ' round-robin=true ' '，流量服务器
基于客户机IP轮询遍历父缓存列表
地址::

dest_host=host1 scheme=http parent="parent1;parent2" round-robin=strict .执行http协议

执行option: ' traffic_ctl config reload '命令应用配置更改。
=ron=
