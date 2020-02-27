# 中容量数传协议

***

### 适用场景:
+ 传输数据总量小于128字节

+ 基于全双工传输协议

+ 从机向主机进行小容量数据传输

+ 主机向从机进行小容量数据传输

+ 无需十分稳定的校验机制

+ 需要支持突发传输

***
### 说明：

这是一个固定长度的传输协议，每个包（数据传输最小单位）的长度均为12字节，每个包的有效数据长度均为8字节（即一个包最多装载8字节的数据）。基本的包元素含有起始帧，包标识符，结束帧。通信时直接将数据包发出，无需进行握手等操作，每帧数据占用一字节（八个二进制位）。

***

### 包内容：

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Contents_cn.jpg" alt="PID Frame" title="PID Frame"  />
##### 帧说明:
+ 帧头：值为0xff的帧

+ 桢尾：值为0xff的帧

+ 包标识符：占用四个位，该值可取0到15，低四位与高四位位反。

  自我校验方式在以下图中说明
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/PID%20Frame_cn.jpg" alt="PID Frame" title="PID Frame" style="zoom: 50%;" />

+ 调整帧：调整数据区以确保数据帧中不含有0xff。如果含有，就会设置相对应的位用于调整帧节，最后清除该数据帧为0x00

  调整方式在下图中说明
 <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Adjust%20Frame_cn.jpg" alt="Adjust Frame" title="Adjust Frame" style="zoom: 50%;" />

***

### 源码移植：

1. 将"src"文件夹中的encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h文件均移植到项目中，并且添加对c标准库string.h的支持
2. 在ioctrl.c文件中实现最基本的发送单个字节功能，即实现Comm_SendChar函数，将Buf发送出去
3. 在接收完成一个字节的数据后，调用ioctrl.c文件的Comm_Rcv函数，将接收的字节传到buf中
4. 完成上述步骤后，调用encrypt中的函数Send_Data即可发送包；接收完成一个包后会触发ioctrl.c中的回调函数Receive_CallBack