# 小容量数传协议

[Switch to English](https://github.com/ZhuYanzhen1/CDTP/blob/master/Small%20Capacity/README.md)

***

### 适用场景:
+ 传输数据总量小于3字节

+ 基于全双工传输协议

+ 从机向主机进行小容量数据传输

+ 主机向从机进行小容量数据传输

+ 无需十分稳定的校验机制

+ 需要支持突发传输

***
### 说明：

这是一个固定长度的传输协议，每个包（数据传输最小单位）的长度均为4字节，每个包的有效数据长度均为3字节（即一个包最多装载3字节的数据）。通信时直接将数据包发出，无需进行握手等操作，每帧数据占用一字节（八个二进制位）。

***

### 包内容：

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Content_s_cn.jpg" alt="PID Frame" title="PID Frame"  />
##### 帧说明:

每一帧的前两位为帧标识符，帧标识符有如上的四种组合，分别代表了四个不同的帧。3字节要传送的数据经过拆分和重组，以每个帧6位有效数据的方式装入每帧中。

***

### 源码移植：

1. 将"src"文件夹中的encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h文件均移植到项目中
2. 在ioctrl.c文件中实现最基本的发送单个字节功能，即实现Comm_SendChar函数，将Buf发送出去
3. 在接收完成一个字节的数据后，调用decrypt.c文件的Comm_Received_CallBack函数，将接收的字节传到buf中
4. 完成上述步骤后，调用encrypt中的函数Send_Data即可发送包；接收完成一个包后会触发ioctrl.c中的回调函数Receive_CallBack