# 数传协议

![Version](https://img.shields.io/badge/Version-1.2.1-brightgreen.svg)&nbsp;&nbsp;![Build](https://img.shields.io/badge/Build-Passed-success.svg)&nbsp;&nbsp;![License](https://img.shields.io/badge/License-AGPL-blue.svg)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[English](https://github.com/ZhuYanzhen1/CDTP/blob/master/README.md) / 中文

***

- [大容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/ldtp/README_CN.md)：传输数据无上限，适用于高性能设备的数据传输

  - RAM占用约128B

- [中等容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README_CN.md)：传输数据不大于128字节，适用于STM32等中高性能设备的数据传输

  - RAM占用约24B
  
- [小容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/sdtp/README_CN.md)：传输数据不大于3字节，适用于51单片机等低性能设备的数据传输
- RAM占用约8B

注：请在满足传输容量的情况下尽量选择小的数据传输协议，因为越大容量的数据传输协议占用的堆栈越大、协议处理越复杂、出错概率越大，体现在单片机上就是中断占用时间更长（呈几何增长）、堆栈更容易溢出。

***

### BUG报告 & 功能需求

请使用[Issue Tracker](https://github.com/ZhuYanzhen1/CDTP/issues)报告错误和需求功能，并遵循以下要求：

1.在不同选项卡上突出显示选项卡。
2.如果窗口未聚焦，不要让更新消失。

***

### 许可证

源代码根据[AGPL-3.0许可证](https://github.com/ZhuYanzhen1/CDTP/blob/master/LICENSE)发布。

**组织：AcmeTech <br>
作者：朱彦臻<br>
维护人：朱彦臻, 2208213223@qq.com**

该产品已经在Windows 10、Ubuntu 18.04和20.04下进行了测试。这是一个研究代码，希望它经常更改，并且不承认任何特定用途的适用性。