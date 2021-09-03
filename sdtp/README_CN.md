# 小容量数传协议

[English](https://github.com/ZhuYanzhen1/CDTP/blob/master/sdtp/README.md) / 中文

### 适用场景:

+ 传输数据总量小于3字节
+ 基于全双工传输协议
+ 从机向主机进行小容量数据传输
+ 主机向从机进行小容量数据传输
+ 无需十分稳定的校验机制
+ 需要支持突发传输

***

### 说明：

&nbsp;&nbsp;&nbsp;&nbsp;这是一个固定长度的传输协议，每个包（数据传输最小单位）的长度均为4字节，每个包的有效数据长度均为3字节（即一个包最多装载3字节的数据）。通信时直接将数据包发出，无需进行握手等操作，每帧数据占用一字节（八个二进制位）。

***

### 包内容：

![PID_Frame](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Package%20Content_s_cn.jpg)

#### 帧说明:

&nbsp;&nbsp;&nbsp;&nbsp;每一帧的前两位为帧标识符，帧标识符有如上的四种组合，分别代表了四个不同的帧。3字节要传送的数据经过拆分和重组，以每个帧6位有效数据的方式装入每帧中。
