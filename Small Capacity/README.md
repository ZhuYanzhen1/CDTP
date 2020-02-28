# Mid Capacity Data Transmit Protocol

[切换到中文](https://github.com/ZhuYanzhen1/CDTP/blob/master/Small%20Capacity/README_CN.md)

***

### Applicable Scenario:
+ The total amount of transmitted data is less than 3 Byte

+ Based on Full-Duplex transmit protocol

+ Mid capacity data transmit from master to slave

+ Mid capacity data transmit from slave to master

+ Don't need  stable transmit

+ Support burst transmission

***
### Description：

This is a fixed-length transmit protocol, each package (the smallest unit of a transmit mission) length is 4Byte, the effective data length is 3Byte(means that the maximum data length is 3Byte). When communicating, sending package directly without handshaking. Each frame occupy a Byte(8 bits).

***

### Package Contents：

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Content_s.jpg" alt="PID Frame" title="PID Frame"  />
##### Frame declaration:

The first two bits of each frame are frame identifiers. There are four combinations of the frame identifiers, representing four different frames. The 3-byte data which have to be transmitted are split and reorganized, and loaded into frame in the way of 6-bit effective data of each frame.

***

### Porting Code：

1. Porting files "encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h" into your project
2.  Realize the single byte transmit function in "ioctrl.c", which function name is Comm_SendChar.
3. After receiving a byte，call the "Comm_Received_CallBack" function in "decrypt.c", as well deliver the received byte to buf.
4. After finished the previous steps，call the "Send_Data" function to send a package; it'll trig the "Receive_CallBack" function in "ioctrl.c" if received a package.