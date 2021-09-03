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

&nbsp;&nbsp;&nbsp;&nbsp;This is a fixed-length transmit protocol, each package (the smallest unit of a transmit mission) length is 12Byte, the effective data length is 8Byte(means that the maximum data length is 8Byte). The base element of a package include SOF(Start Of Frame), PID(Package Identification) and EOF(End Of Frame). When communicating, sending package directly without handshaking. Each frame occupy a Byte(8 bits).

***

### Package Contents：

![Package_Contents](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Package%20Contents.jpg)

##### Frame declaration:

+ SOF(Start of frame): The initial frame of a package, which value is 0xff.
+ EOF(End of frame): The final frame of a package, which value is 0xff.
+ ADJ(Adjust frame): adjust data area to make sure data frame haven't exist 0xff. If data frame appeared 0xff, set corresponding bit in adjust frame then clear the data frame as 0x00. The corresponding relationship is as below image.
  ![Adjust Frame](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Adjust%20Frame.jpg)

+ PID(Package identification): occupied 4 bits, values range from 0 to 15. Low 4 bits is the inverse of the High 4bits. The self checking method is as below image.
  ![PID_Frame](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/PID%20Frame.jpg)
