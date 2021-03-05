Inline on a Linux router
************************

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

The routed set up presumes the set of clients are on distinct networks
behind a single physical interface. For the purposes of this example
will we presume

-  The clients are on network 172.28.56.0/24
-  The router connects the networks 172.28.56.0/24 and 192.168.1.0/24
-  Interface ``eth0`` is on the network 192.168.1.0/24
-  Interface ``eth1`` is on the network 172.28.56.0/24
-  The router is already configured to route traffic correctly for the
   clients.

In this example we will intercept port 80 (HTTP) traffic that traverses
the router. The first step is to use ``iptables`` to handle IP packets
appropriately.

::

    # reflow client web traffic to TPROXY
    iptables -t mangle -A PREROUTING -i eth1 -p tcp -m tcp --dport 80 -j TPROXY \
       --on-ip 0.0.0.0 --on-port 8080 --tproxy-mark 1/1
    # Let locally directed traffic pass through.
    iptables -t mangle -A PREROUTING -i eth0 --source 192.168.1.0/24 -j ACCEPT
    iptables -t mangle -A PREROUTING -i eth0 --destination 192.168.1.0/24 -j ACCEPT
    # Mark presumed return web traffic
    iptables -t mangle -A PREROUTING -i eth0 -p tcp -m tcp --sport 80 -j MARK --set-mark 1/1

We mark packets so that we can use policy routing on them. For inbound
packets we use ``TPROXY`` to make it possible to accept packets sent to
foreign IP addresses. For returning outbound packets there will be a
socket open bound to the foreign address, we need only force it to be
delivered locally. The value for ``--on-ip`` is 0 because the target
port is listening and not bound to a specific address. The value for
``--on-port`` must match the Traffic Server server port. Otherwise its
value is arbitrary. ``--dport`` and ``--sport`` specify the port from
the point of view of the clients and origin servers. The middle two
lines exempt local web traffic from being marked for Traffic Server --
these rules can be tightened or loosened as needed. They server by
matching traffic and exiting the ``iptables`` processing via ``ACCEPT``
before the last line is checked.

Once the flows are marked we can force them to be delivered locally via
the loopback interface via a policy routing table.

::

    ip rule add fwmark 1/1 table 1
    ip route add local 0.0.0.0/0 dev lo table 1

The marking used is arbitrary but it must be consistent between
``iptables`` and the routing rule. The table number must be in the range
1..253.

To configure Traffic Server set the following values in
:file:`records.config`

``proxy.config.http.server_ports``
    ``STRING``
    Default: *value from* ``--on-port``

``proxy.config.reverse_proxy.enabled``
    ``INT``
    Default: ``1``

``proxy.config.url_remap.remap_required``
    ``INT``
    Default: ``0``


=ron=
内嵌在Linux路由器上
* * * * * * * * * * * * * * * * * * * * * * * *

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

路由设置假定客户端是在不同的网络上
在单个物理接口后面。为了本例的目的
我们会认为

—客户端所在网络为“172.28.56.0/24”
—连接172.28.56.0/24和192.168.1.0/24两个网络
—“eth0”接口位于192.168.1.0/24网络中
—接口“eth1”在网络“172.28.560 /24”上
—路由器已经配置为正确路由流量
客户。

在本例中，我们将拦截经过的端口80 (HTTP)流量
路由器。第一步是使用“iptables”来处理IP数据包
适当。

::

# reflow客户端web流量到TPROXY
iptables -t mangle -A PREROUTING -i eth1 -p tcp -m tcp——dport 80 -j TPROXY \
——on-ip 0.0.0.0——on-port 8080——tproxy-mark 1/1
#让本地引导的车辆通过。
iptables -t mangle -A PREROUTING -i eth0——source 192.168.1.0/24 -j ACCEPT
iptables -t mangle -A PREROUTING -i eth0——destination 192.168.1.0/24 -j ACCEPT
#标记假定返回的web流量
iptables -t mangle -A PREROUTING -i eth0 -p tcp -m tcp——sport 80 -j MARK——set-mark 1/1

我们标记包，以便我们可以在它们上使用策略路由。对于入站
我们使用“TPROXY”使接收发送到的数据包成为可能
外国的IP地址。对于返回的出站数据包，将有一个
套接字打开绑定到外部地址，我们只需要强制它是
在本地交付。“——on-ip”的值为0，因为目标
端口正在监听，但没有绑定到特定的地址。的值
' '——on-port ' '必须与流量服务器的服务器端口匹配。否则它
值是任意的。' ' '——dport ' '和' '——sport ' '指定端口
客户端和源服务器的观点。中间两个
线路免除本地web流量被标记为流量服务器——
这些规则可以根据需要加强或放松。他们服务器
匹配流量并通过“ACCEPT”退出“iptables”处理
在检查最后一行之前。

一旦流被标记，我们就可以强制它们在本地通过
loopback接口通过策略路由表。

::

ip规则添加fwmark 1/1表1
ip route add local 0.0.0.0/0 dev lo表1

所使用的标记是任意的，但必须是一致的
' '和路由规则。表号必须在范围内
1 . . 253。

要配置流量服务器，请在
:文件:“records.config”

“proxy.config.http.server_ports ' '
' '字符串' '
默认值:* from* ``——on-port``

“proxy.config.reverse_proxy.enabled ' '
' ' INT ' '
默认值:' ' 1 ' '

“proxy.config.url_remap.remap_required ' '
' ' INT ' '
默认值:' ' 0 ' '
=ron=

