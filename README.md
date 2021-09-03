# Data Transmit Protocol

![Version](https://img.shields.io/badge/Version-1.2.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;English / [中文](https://github.com/ZhuYanzhen1/CDTP/blob/master/README_CN.md)

- [Large Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/ldtp/README.md): Infinite data length
- [Mid Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README.md): Data length is less than 128Byte
- [Small Capacity Data Transmit Protocol](https://github.com/ZhuYanzhen1/CDTP/blob/master/sdtp/README.md): Data length is less than 3Byte

***

### Porting Code：

1. Porting files "encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h" into your project
2. Realize the single byte transmit function in "ioctrl.c", which function name is Comm_SendChar.
3. After receiving a byte，call the "Comm_Received_CallBack" function in "decrypt.c", as well deliver the received byte to buf.
4. After finished the previous steps，call the "Send_Data" function to send a package; it'll trig the "Receive_CallBack" function in "ioctrl.c" if received a package.

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