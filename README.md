# Capacity Data Transmit Protocol

***

### Applicable Scenario:
+ Based on Half-Duplex transmit protocol

+ High capacity data transmit from slave to master

+ Low capacity data transmit from master to slave

+ Stable transmit with retransmit function and Answer function

+ Various data checking methods

+ Support burst transmission

***

### Description:
This is a varying length transmit protocol, which maximum data length is 14 Byte and minimum is 3 Byte. The base element of a package include SOF(Start Of Frame), PID(Package Identification) and EOF(End Of Frame). A communication is established by a Handshake package from master device, and every data or control package requires an Answer package from another device. Each frame occupy a Byte(8 bits).
***
![PID Corresponding PC](https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Type%20Corresponding%20Package%20Content.jpg "PID Corresponding PC")

|   Package Function   |                     Package Description                      |
| :------------------: | :----------------------------------------------------------: |
|  Handshake Package   | Start flag of a communication, firstly send by master device, then slave device answer with the same package. |
|   Answered Package   | To answer every data or control package send from another device. |
| Fully Filled Package | A package represented a data package which every data frame (in data area) is 0xff |
|    Abort Package     | End flag of a communication whether the communicate is finished |
|  Reset UID Package   |     To set the UID(unique identification) frame as 0x00      |
|  Retransmit Package  |    Require another device to retransmit the error package    |
|   Request Package    | Send a request from master to slave, slave device transmit corresponding data to master device. |
| DATA0/DATA1 Package  | When do high capacity transmit task, DATA0 package and DATA1 package should use alternates with each other. |
|     Idle Package     | Reserve package for small amount of data or command transmission |

##### Frame declaration:
+ SOF(Start of frame): The initial frame of a package, which value is 0xff.
+ EOF(End of frame): The final frame of a package, which value is 0xff.
+ PID(Package identification): the identification of a package, has self checking.
+ CRC(Cyclic redundancy check): check form PID frame to CRC frame.
+ UID(Unique identification): unique identification for every data package.
+ ADJ(Adjust frame): adjust data area to make sure data frame haven't exist 0xff.