# Mid Capacity Data Transmit Protocol

English / [中文](https://github.com/ZhuYanzhen1/CDTP/blob/master/mdtp/README_CN.md)

### Applicable Scenario:
+ The total amount of transmitted data is less than 128 Byte

+ Based on Full-Duplex transmit protocol

+ Mid capacity data transmit from master to slave

+ Mid capacity data transmit from slave to master

+ Don't need stable transmit

+ Support burst transmission

***
### Description：

This is a fixed-length transmit protocol, each package (the smallest unit of a transmit mission) length is 12Byte, the effective data length is 8Byte(means that the maximum data length is 8Byte). The base element of a package include SOF(Start Of Frame), PID(Package Identification) and EOF(End Of Frame). When communicating, sending package directly without handshaking. Each frame occupy a Byte(8 bits).

***

### Package Contents：

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Package%20Contents.jpg" alt="PID Frame" title="PID Frame"  />
##### Frame declaration:
+ SOF(Start of frame): The initial frame of a package, which value is 0xff.

+ EOF(End of frame): The final frame of a package, which value is 0xff.

+ ADJ(Adjust frame): adjust data area to make sure data frame haven't exist 0xff. If data frame appeared 0xff, set corresponding bit in adjust frame then clear the data frame as 0x00.

  The corresponding relationship is as below image.
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Adjust%20Frame.jpg" alt="Adjust Frame" title="Adjust Frame" style="zoom: 50%;" />

+ PID(Package identification): occupied 4 bits, values range from 0 to 15. Low 4 bits is the inverse of the High 4bits.

  The self checking method is as below image.
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/PID%20Frame.jpg" alt="PID Frame" title="PID Frame" style="zoom: 50%;" />

***

### Porting Code：

1. Porting files "encrypt.c，encrypt.h，decrypt.c，decrypt.h，ioctrl.c，ioctrl.h" into your project，then add the support of standard c lib "string.h"
2.  Realize the single byte transmit function in "ioctrl.c", which function name is Comm_SendChar.
3. After receiving a byte，call the "Comm_Rcv" function in "ioctrl.c", as well deliver the received byte to buf.
4. After finished the previous steps，call the "Send_Data" function to send a package; it'll trig the "Receive_CallBack" function in "ioctrl.c" if received a package.