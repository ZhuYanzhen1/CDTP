# Small Capacity Data Transmit Protocol

English / [中文](https://github.com/ZhuYanzhen1/CDTP/blob/master/sdtp/README_CN.md)

### Applicable Scenario:

+ The total amount of transmitted data is less than 3 Byte
+ Based on Full-Duplex transmit protocol
+ Mid capacity data transmit from master to slave
+ Mid capacity data transmit from slave to master
+ Don't need  stable transmit
+ Support burst transmission

***

### Description：

&nbsp;&nbsp;&nbsp;&nbsp;This is a fixed-length transmit protocol, each package (the smallest unit of a transmit mission) length is 4Byte, the effective data length is 3Byte(means that the maximum data length is 3Byte). When communicating, sending package directly without handshaking. Each frame occupy a Byte(8 bits).

***

### Package Contents：

![PID_Frame](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/image/Package%20Content_s.jpg)

#### Frame declaration:

&nbsp;&nbsp;&nbsp;&nbsp;The first two bits of each frame are frame identifiers. There are four combinations of the frame identifiers, representing four different frames. The 3-byte data which have to be transmitted are split and reorganized, and loaded into frame in the way of 6-bit effective data of each frame.
