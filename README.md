# Data Transmit Protocol

![Version](https://img.shields.io/badge/Version-1.2.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;English / [中文](https://github.com/ZhuYanzhen1/CDTP/blob/master/README_CN.md)

&nbsp;&nbsp;&nbsp;&nbsp;This project is a derivative version of a lightweight data transmission protocol proposed and developed by the author when he participated in [Robomaster high school summer camp](https://www.robomaster.com/zh-CN/campus/highSchool?djiFrom=HEAD) in senior three. The main purpose is to realize the function of the transport layer. This protocol can be applied to various physical layers, such as UART, SPI, IIC, etc., which provides a guarantee for sequential data transmission. According to the requirements of the amount of data transmitted, the author divides the protocol into the following three different versions:

- [Large Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/ldtp/README.md): Infinite data length
- [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README.md): Data length is less than 128Byte
- [Small Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/sdtp/README.md): Data length is less than 3Byte

&nbsp;&nbsp;&nbsp;&nbsp;Note: please try to choose a small data transmission protocol when the transmission capacity is met, because the larger the data transmission protocol, the larger the stack, the more complex the protocol processing and the greater the error probability, which is reflected in the longer interrupt occupation time (geometric increase) and the easier the stack overflow on the single chip microcomputer.

***

### Porting Code：

1. Porting files "encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h" into your project
2. Realize the single byte transmit function in "ioctrl.c", which function name is common_sendbyte.
3. After receiving a byte，call the "common_receivebyte" function in "decrypt.c", as well deliver the received byte to buf.
4. After finished the previous steps，call the "xdtp_data_transmit" function to send a package; it'll trig the "xdtp_callback_handler" function in "ioctrl.c" if received a package.

***

### Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/ZhuYanzhen1/CDTP/issues) and follow these request:

1. Tab highlight when on different tab.
2. Don’t let the update disappear if the window is not in focus.

***

### License

The source code is released under a [AGPL-3.0 License](https://github.com/ZhuYanzhen1/CDTP/blob/master/LICENSE).

**Affiliation：AcmeTech<br>
Author: Zhu Yanzhen<br>
Maintainer：YanzhenZhu, 2208213223@qq.com**

The product has been tested under Windows 10 and Ubuntu 18.04 and 20.04. This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed.