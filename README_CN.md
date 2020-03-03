# 数传协议

作者：朱彦臻
[Switch to English](https://github.com/ZhuYanzhen1/CDTP/blob/master/README.md)

***

- [大容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/Large%20Capacity/README_CN.md)：传输数据无上限，适用于高性能设备的数据传输

  - RAM占用约128B

- [中等容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/Mid%20Capacity/README_CN.md)：传输数据不大于128字节，适用于STM32等中高性能设备的数据传输

  - RAM占用约24B
  
- [小容量数据传输](https://github.com/ZhuYanzhen1/CDTP/blob/master/Small%20Capacity/README_CN.md)：传输数据不大于3字节，适用于51单片机等低性能设备的数据传输

  - RAM占用约8B

注：请在满足传输容量的情况下尽量选择小的数据传输协议，因为越大容量的数据传输协议占用的堆栈越大、协议处理越复杂、出错概率越大，体现在单片机上就是中断占用时间更长（呈几何增长）、堆栈更容易溢出。