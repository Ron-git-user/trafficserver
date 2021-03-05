.. _building-ats-for-transparency:

Building ATS for transparency
*****************************

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


In most cases, if your environment supports transparency then
``configure`` will automatically enable it. For other environments you
may need to twiddle the ``configure`` options.

``--enable-posix-cap``
    This enables POSIX capabilities, which are required for
    transparency. These are compiled in by default. To check your
    system, look for the header file ``sys/capability.h`` and the system
    library ``libcap``. These are in the packages ``libcap`` and
    ``libcap-devel`` or ``libcap-dev`` (depending on the Distribution)
    contra-respectively.

``--enable-tproxy[=value]``
    Enable TPROXY support, which is the Linux kernel feature used for
    transparency. This should be present in the base installation, there
    is no package associated with it. \* ``auto`` Do automatic checks
    for the TPROXY header file (``linux/in.h``) and enable TPROXY
    support if the ``IP_TRANSPARENT`` definition is present. This is the
    default if this option is not specified or ``value`` is omitted. \*
    ``no`` Do not check for TPROXY support, disable support for it. \*
    ``force`` Do not check for TPROXY support, enable it using the $ats@
    built in value for ``IP_TRANSPARENT``. This is useful for systems
    that have it in the kernel for but some reason do not have the
    appropriate system header file. \* *number* Do not check for TPROXY
    support, use *number* as the ``IP_TRANSPARENT`` value. There are, at
    present, no known standard distributions of Linux that support
    TPROXY but use a value different from the built in ATS default.
    However, a custom built kernel may do so and in that case the
    specific value can be specified.

In the default case, ATS configuration will automatically check for
TPROXY support via the presence of the ``linux/in.h`` header file and
compile in TPROXY support if it is available. If that fails, you may be
able to recover by using one of the options above. Note that
transparency may be built in by default but it is not active unless
explicitly enabled in the ATS configuration files.


=ron=
. ._building-ats-for-transparency:

建立自动测试系统以提高透明度
*****************************

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


在大多数情况下，如果您的环境支持透明性，那么
' ' '配置' ' '将自动启用它。对于其他环境，您可以
可能需要拨弄“配置”选项。

“——enable-posix-cap ' '
这将启用POSIX功能，这是必需的
透明度。默认情况下，这些是编译的。来检查你
系统，查找头文件' ' sys/capability。h ' '和方程组
图书馆从googlecode获得libcap ' ' ' '。这些是在包' ' libcap ' '和
' libcap-devel '或' libcap-dev '(取决于发行版)
contra-respectively。

“——enable-tproxy[=价值]' '
启用TPROXY支持，这是Linux内核特性的用途
透明度。这应该存在于基础安装中
没有与它相关联的包。\* ' ' auto ' '做自动检查
对于TPROXY头文件(' ' linux/in.h ' ')，并启用TPROXY
如果' ' IP_TRANSPARENT ' '定义存在，则支持。这是
默认值，如果未指定此选项或省略' ' value ' '。\ *
' ' no ' ' '不要检查TPROXY支持，禁用它的支持。\ *
不要检查TPROXY支持，使用$ats@启用它
内置值为' ' IP_TRANSPARENT ' '。这对于系统是很有用的
因为某些原因在内核中没有
适当的系统头文件。\* *number*不要检查TPROXY
支持，使用*number*作为' ' IP_TRANSPARENT ' '值。有,在
目前，没有已知的支持Linux的标准发行版
TPROXY，但使用与内置ATS默认值不同的值。
但是，定制的内核可以这样做，在这种情况下
可指定具体值。

默认情况下，ATS配置会自动检查
TPROXY支持通过' ' linux/in的存在。h ' '头文件和
如果可以的话，在TPROXY支持中编译。如果失败了，你可能会失败
能够通过使用上面的选项之一恢复。请注意,
默认情况下，透明度可能是内置的，但它不是激活的，除非
在ATS配置文件中显式启用。
=ron=

