Inline on a Linux Bridge
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
=ron=
   内联在Linux网桥上
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
=ron=



A Linux can be configured to operate in `bridge mode <http://www.linuxfoundation.org/collaborate/workgroups/networking/bridge>`_.
Two or more physical interfaces are assigned to the bridge. A single IP
address is shared across the interfaces. By default any packet that
arrives on one interface is immediately routed out another bridge
interface.

Linux packages required:

-  bridge-utils
-  ebtables

=ron=
Linux可以配置为'网桥模式<http: www.linuxfoundation.org="" collaborate="" workgroups="" networking="" bridge=""> ' _。</http:>
两个或多个物理接口被分配给网桥。一个单一的IP
地址是跨接口共享的。缺省情况下，任何
到达一个接口后立即路由出另一个桥
接口。

Linux包要求:

——bridge-utils
——ebtables
=ron=


In our example of setting up bridge mode we will use a local address of
192.168.1.11/24 and interfaces ``eth0`` and ``eth1`` as the bridge
interfaces (more detailed documentation is available
`here <http://www.tldp.org/HOWTO/BRIDGE-STP-HOWTO/preparing-the-bridge.html>`_).
You may omit the '#' character and everything after it. ::

   brctl addbr br0 # create bridge device
   brctl stp br0 off # Disable spanning tree protocol
   brctl addif br0 eth0 # Add eth0 to bridge
   brctl addif br0 eth1 # Add eth1 to bridge

   ifconfig eth0 0 0.0.0.0 # Get rid of interface IP addresses
   ifconfig eth1 0 0.0.0.0 # ditto # Set the bridge IP address and enable it
   ifconfig br0 192.168.1.11 netmask 255.255.255.0 up

If you have not already done so, remember to add a default route, such
as this one for a gateway of 192.168.1.1. ::

   ip route add default via 192.168.1.1

At this point it is a good idea to test connectivity to verify the basic
bridge is functional.

Once the bridge is verified to work, this is the basic traffic pattern
of interest.

.. figure:: ../../../static/images/admin/ats-traffic-bridge.png
   :align: center
   :alt: Picture of traffic flow through a bridge with ATS

   Picture of traffic flow through a bridge with ATS

The green arrows are packets originating from the client and the red
arrows are packets originating from the origin server. All traffic not
directed to the local address will pass through the bridge. We need to
break into some of the traffic and subject it to routing so that it can
be routed to ATS. This requires ``ebtables``. The flows we want to
intercept are green 1 (from client to bridge) and red 1 (origin server
to bridge).

=ron=
在我们建立网桥模式的例子中，我们将使用本地地址
192.168.1.11/24，接口“eth0”和“eth1”作为网桥
接口(可以获得更详细的文档
这里< http://www.tldp.org/HOWTO/BRIDGE-STP-HOWTO/preparing-the-bridge.html > _)。
您可以省略“#”字符及其后面的所有内容。::

brctl addbr br0 #创建桥接设备
brctl stp br0 off #关闭生成树协议
brctl addif br0 eth0 #将eth0添加到网桥中
brctl addif br0 eth1 #添加eth1到网桥

ifconfig eth0 0 0.0.0.0 #删除接口IP地址
ifconfig eth1 0 0.0.0.0 # ditto #设置网桥IP地址并使能
ifconfig br0 192.168.1.11 netmask 255.255.255.0 up

如果您还没有这样做，请记住添加一个默认路由，例如
作为网关192.168.1.1的这一个。::

ip route add default via 192.168.1.1

此时，测试连接性以验证基本的
桥是功能。

一旦这座桥被证实可以使用，这就是基本的交通模式
感兴趣的。

. .图 :: ../../../ 静态/图片/ admin / ats-traffic-bridge.png
对齐:中心
:alt:使用ATS的桥上交通流量图片

配备ATS的大桥上的车流图片

绿色箭头表示来自客户端的数据包，红色箭头表示来自客户端的数据包
箭头是来自源服务器的数据包。所有流量不
直接到本地地址将通过桥。我们需要
闯入一些交通，让它按照路线行驶，这样它就能
路由到ATS。这需要“ebtables ' '。我们想要的流动
截距为绿色1(从客户端到网桥)和红色1(原始服务器)
桥)。
=ron=

In this example we will intercept port 80 (HTTP) traffic. We will use
the ``BROUTING`` chain because it is traversed only for packets that
originated externally and arrived on a (forwarding enabled) interface.
Although it looks like this will intercept all port 80 traffic it will
only affect the two flows described above. ``-j redirect`` marks the
packet as being diverted to the bridge and not forwarded, and the
``DROP`` target puts the packets in the normal ``iptables`` routing so
that we can use standard device tests on them [1]_. Although this
example handles only port 80, other ports are the same except for the
port value. Note also the port here is the port from the point of view
of the clients and origin servers, not the Traffic Server server port. ::

   ebtables -t broute -F # Flush the table
   # inbound traffic
   ebtables -t broute -A BROUTING -p IPv4 --ip-proto tcp --ip-dport 80 \
     -j redirect --redirect-target DROP
   # returning outbound traffic
   ebtables -t broute -A BROUTING -p IPv4 --ip-proto tcp --ip-sport 80 \
     -j redirect --redirect-target DROP

Traffic Server operates at layer 3 so we need to use ``iptables`` to
handle IP packets appropriately.::

   iptables -t mangle -A PREROUTING -i eth1 -p tcp -m tcp --dport 80 \
     -j TPROXY --on-ip 0.0.0.0 --on-port 8080 --tproxy-mark 1/1
   iptables -t mangle -A PREROUTING -i eth0 -p tcp -m tcp --sport 80 \
      -j MARK --set-mark 1/1

At this point the directionality of the interfaces matters. For the
example ``eth1`` is the inbound (client side) interface, while ``eth0``
is the outbound (origin server side) interface. We mark both flows of
packets so that we can use policy routing on them. For inbound packets
we need to use ``TPROXY`` to force acceptance of packets to foreign IP
addresses. For returning outbound packets there will be a socket open
bound to the foreign address, we need only force it to be delivered
locally. The value for ``--on-ip`` is 0 because the target port is
listening and not bound to a specific address. The value for
``--on-port`` must match the Traffic Server server port. Otherwise its
value is arbitrary. ``--dport`` and ``--sport`` specify the port from
the point of view of the clients and origin servers.

Once the flows are marked we can force them to be delivered locally via
the loopback interface via a policy routing table.::

   ip rule add fwmark 1/1 table 1
   ip route add local 0.0.0.0/0 dev lo table 1

The marking used is arbitrary but it must be consistent between
``iptables`` and the routing rule. The table number must be in the range
1..253.

To configure Traffic Server set the following values in
:file:`records.config`

- :ts:cv:`proxy.config.http.server_ports` *value from* ``--on-port`` (see below)

- :ts:cv:`proxy.config.reverse_proxy.enabled` ``1``

- :ts:cv:`proxy.config.url_remap.remap_required` ``0``

Additional troubleshooting
~~~~~~~~~~~~~~~~~~~~~~~~~~

=ron=
在本例中，我们将拦截端口80 (HTTP)流量。我们将使用
“BROUTING”链，因为它只对数据包进行遍历
起源于外部并到达(启用转发)接口。
虽然看起来这能拦截所有80端口的通信，它能
只影响上面描述的两个流。' ' -j redirect ' '标记
数据包被转移到桥上而没有被转发，并且
' ' DROP ' '目标将数据包放入正常的' ' iptables ' '路由中
我们可以对它们进行标准设备测试[1]_。虽然这
只处理端口80，其他端口相同，除了
端口值。还要注意，从这个角度来看，这里的端口就是端口
客户端和源服务器的端口，而不是流量服务器的服务器端口。::

ebtables -t broute - f#刷新表
#入站流量
ebtables -t broute -A BROUTING -p IPv4——ip-proto tcp——ip-dport 80 \
-j redirect——重定向目标删除
返回出站流量
ebtables -t broute -A BROUTING -p IPv4——ip-proto tcp——ip-sport 80 \
-j redirect——重定向目标删除

流量服务器在第三层运行，所以我们需要使用iptables
适当地处理IP数据包。

iptables -t mangle -A PREROUTING -i eth1 -p tcp -m tcp——dport 80 \
-j TPROXY——on-ip 0.0.0.0——on-port 8080——TPROXY -mark 1/1
iptables -t mangle -A PREROUTING -i eth0 -p tcp -m tcp——sport 80 \
-j MARK——set-mark 1/1

在这一点上，接口的方向性很重要。为
示例' ' eth1 ' '是入站(客户端)接口，而' ' eth0 ' '
是出站(源服务器端)接口。我们标记这两个流
数据包，这样我们就可以对它们使用策略路由。对于入站信息包
我们需要使用“TPROXY”来强制外部IP接收数据包
地址。对于返回出站数据包，将打开一个套接字
绑定到国外地址，我们只需要强制交付
本地。“——on-ip”的值为0，因为目标端口为
监听而不绑定到特定的地址。的值
' '——on-port ' '必须与流量服务器的服务器端口匹配。否则它
值是任意的。' ' '——dport ' '和' '——sport ' '指定端口
客户端和源服务器的观点。

一旦流被标记，我们就可以强制它们在本地通过
loopback接口通过策略路由表。

ip规则添加fwmark 1/1表1
ip route add local 0.0.0.0/0 dev lo表1

所使用的标记是任意的，但必须是一致的
' '和路由规则。表号必须在范围内
1 . . 253。

要配置流量服务器，请在
:文件:“records.config”

-: ts:简历:“proxy.config.http。——on-port '(见下面)

-: ts:简历:“proxy.config.reverse_proxy。使' ' ' 1 ' '

-: ts:简历:“proxy.config.url_remap。remap_required ' ' ' 0 ' '

额外的故障排除
~~~~~~~~~~~~~~~~~~~~~~~~~~
=ron=


* Check to make sure that ``iptables`` is not filtering (blocking)
  incoming HTTP connections.

   It is frequently the case that the default tables prevent incoming HTTP. You can clear all filters with the
   commands::

      iptables -t filter --flush FORWARD
      iptables -t filter --flush INPUT

   That is a bit drastic and should only be used for testing / debugging. A
   live system will likely need some filters in place but that is beyond
   the scope of this document. If this fixes the problem, then your filter
   set is too restrictive.

   Note that this problem will prevent the basic bridge (without ATS) from
   allowing HTTP traffic through.

* Verify that IP packet forwarding is enabled.

   You can check this with::

      cat /proc/sys/net/ipv4/ip_forward

   The output should be a non-zero value (usually '1'). If it is zero, you
   can set it with::

      echo '1' > /proc/sys/net/ipv4/ip_forward

   This can setting can be persisted by putting it in ``/etc/sysctl.conf``: ::

      net/ipv4/ip_forward=1

.. rubric:: Footnotes

.. [1]
   The ``--redirect-target`` can be omitted, but then the ``iptables``
   rules would need to use ``--physdev`` instead of just ``-i``. The
   actual packet processing is identical.


=ron=
检查iptables是否被过滤(阻塞)
传入的HTTP连接。

通常情况下，默认表会阻止传入的HTTP。属性可以清除所有过滤器
命令:

iptables -t filter——flush FORWARD
iptables -t filter——flush INPUT

这有点极端，应该只用于测试/调试。一个
live system可能需要一些适当的过滤器，但那是超出的
本文件的范围。如果这解决了问题，那么你的过滤器
set的限制太大。

注意，这个问题将阻止基本桥接(没有ATS)
允许HTTP通信通过。

*验证IP报文转发功能是否开启。

你可以用:

猫/proc/sys/net/ipv4/ip_forward

输出应该是一个非零值(通常是'1')。如果它是零，你
可以设置为::

echo '1' > /proc/sys/net/ipv4/ip_forward

这个can设置可以通过' ' /etc/sysctl保存。参看“:::

net/ipv4/ip_forward = 1

. .标题:脚注

. .[1]
——redirect-target可以省略，但是iptables可以省略。
规则需要使用' '——physdev ' '，而不是' ' -i ' '。的
实际的数据包处理是相同的。
=ron=
