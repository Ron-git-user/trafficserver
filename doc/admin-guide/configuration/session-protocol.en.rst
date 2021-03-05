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

.. _session-protocol:

Session Protocol
****************

|TS| supports some session level protocols in place of or on top of HTTP. These
can be provided by a plugin (see :ref:`developer-plugins-new-protocol-plugins`)
or be one that is supported directly by |TS|.

Session protocols are specified by explicit names:

*  ``http/0.9``
*  ``http/1.0``
*  ``http/1.1``
*  ``http/2``

The session protocols supported on a proxy port are a subset of these values.
For convenience some pseudo-values are defined in terms of these fundamental
protocols:

*  ``http`` means ``http/0.9``, ``http/1.0``, and ``http/1.1``
*  ``http2`` means ``http/2``

Each proxy port can be configured in :ts:cv:`proxy.config.http.server_ports`
to support a subset of these session protocols. For TLS enabled connections this
configuration controls which protocols are offered by NPN. Protocol sniffing is
use for non-TLS proxy ports to determine which protocol is being used by the
client. If the detected protocol is not supported for that proxy port the
connection is dropped.

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

. ._session-protocol:

会话协议
****************

|支持一些会话级别的协议来代替HTTP或在HTTP之上。这些
可以通过插件提供(参见:ref: ' developer-plugins-new-protocol-plugins ')
或者是|TS|直接支持的。

会话协议由显式名称指定:

*“http / 0.9 ' '
*“http / 1.0 ' '
*“http / 1.1 ' '
*“http / 2 ' '

代理端口上支持的会话协议是这些值的子集。
为了方便起见，一些伪值是根据这些基本值定义的
协议:

*“http”意味着“http / 0.9 ' ',“http / 1.0“,“http / 1.1 ' '
*“http2”的意思是“http/2”

每个代理端口可以配置在:ts:cv: ' proxy.config.http.server_ports '
来支持这些会话协议的一个子集。对于启用TLS的连接
配置控制NPN提供哪些协议。协议嗅探
用于非tls代理端口，以确定哪个协议正在被使用
客户端。如果检测到的协议不支持该代理端口
连接被删除。
=ron=
