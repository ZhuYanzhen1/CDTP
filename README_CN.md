# 数传协议

![Version](https://img.shields.io/badge/Version-2.0.0-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[English](./README.md) / 中文

&nbsp;&nbsp;&nbsp;&nbsp;这个项目是作者在高三参加[Robomaster高中生夏令营](https://www.robomaster.com/zh-CN/campus/highSchool?djiFrom=HEAD)时提出并制定的一个轻量的数传协议的衍生版本，主要目的是实现传输层的功能。这个协议可以被运用在各种物理层上，比如UART、SPI、IIC等，为顺序传输数据提供了保证。根据传输数据量大小的需求，作者将协议分为了以下三个不同的版本：

- [大容量数据传输](./ldtp/README_CN.md)：传输数据无上限，适用于高性能设备的数据传输
- [中等容量数据传输](./mdtp/README_CN.md)：传输数据不大于128字节，适用于STM32等中高性能设备的数据传输
- [小容量数据传输](./sdtp/README_CN.md)：传输数据不大于3字节，适用于51单片机等低性能设备的数据传输

&nbsp;&nbsp;&nbsp;&nbsp;**注：请在满足传输容量的情况下尽量选择小的数据传输协议，因为越大容量的数据传输协议占用的堆栈越大、协议处理越复杂、出错概率越大，体现在单片机上就是中断占用时间更长（呈几何增长）、堆栈更容易溢出。**

***

### 源码移植：

1. 将"src"文件夹中的encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h文件均移植到项目中。
2. 在ioctrl.c文件中实现最基本的发送单个字节功能，即实现common_sendbyte函数，将data发送出去。
3. 在接收完成一个字节的数据后，调用decrypt.c文件的common_receivebyte函数，将接收的字节传到data中。
4. 完成上述步骤后，调用encrypt中的函数xdtp_data_transmit即可发送包；接收完成一个包后会触发ioctrl.c中的回调函数xdtp_callback_handler。

***

### BUG报告 & 功能需求

请使用[Issue Tracker](https://github.com/ZhuYanzhen1/CDTP/issues)报告错误和需求功能，并遵循以下要求：

1. 在不同选项卡上突出显示选项卡。
2. 如果窗口未聚焦，不要让更新消失。

***

### 许可证

源代码根据[AGPL-3.0许可证](https://github.com/ZhuYanzhen1/CDTP/blob/master/LICENSE)发布。

**组织：AcmeTech <br>
作者：朱彦臻<br>
维护人：朱彦臻, 2208213223@qq.com**

该产品已经在Windows 10、Ubuntu 22.04 LTS下进行了测试。这是一个研究代码，希望它经常更改，并且不承认任何特定用途的适用性。