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
<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Type%20Corresponding%20Package%20Content.jpg" alt="PID Corresponding PC" title="PID Corresponding PC"  />

|   Package Function    |                     Package Description                      |
| :-------------------: | :----------------------------------------------------------: |
|   Handshake Package   | Start flag of a communication, firstly send by master device, then slave device answer with the same package. |
|   Answered Package    | To answer every data or control package send from another device. |
| Fully Filled Package  | A package represented a data package which every data frame (in data area) is 0xff |
|     Abort Package     | End flag of a communication whether the communicate is finished |
| ~~Reset UID Package~~ |   ~~To set the UID(unique identification) frame as 0x00~~    |
|  Retransmit Package   |    Require another device to retransmit the error package    |
|    Request Package    | Send a request from master to slave, slave device transmit corresponding data to master device. |
|  DATA0/DATA1 Package  | When do high capacity transmit task, DATA0 package and DATA1 package should use alternates with each other. |
|     Idle Package      | Reserve package for small amount of data or command transmission |

##### Frame declaration:
+ SOF(Start of frame): The initial frame of a package, which value is 0xff.

+ EOF(End of frame): The final frame of a package, which value is 0xff.

+ UID(Unique identification): unique identification for every data package.

+ CRC(Cyclic redundancy check): check form PID frame to CRC frame.

```c
unsigned char calculate_crc8(unsigned char *ptr, unsigned char len) 
{
    unsigned char  crc_result = 0x00;
    while (len--)
    {
        crc_result = crc_table[crc ^ *ptr++];
        //crc_table is at the end of this document
    }
    return (crc);
}
```

+ ADJ(Adjust frame): adjust data area to make sure data frame haven't exist 0xff. If data frame appeared 0xff, set corresponding bit in adjust frame then clear the data frame as 0x00.

  The corresponding relationship is as below image.
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Adjust%20Frame.jpg" alt="Adjust Frame" title="Adjust Frame" style="zoom: 50%;" />

+ PID(Package identification): occupied 4 bits, values range from 0 to 15. Low 4 bits is the inverse of the High 4bits.

  The self checking method is as below image.
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/PID%20Frame.jpg" alt="PID Frame" title="PID Frame" style="zoom: 50%;" />

+ Err_Type: the type of error package received previous.
  
    - 0: Lost EOF or SOF (two 0xff frame adjacent appeared)
    - 1: CRC value unequal
    - 2: Data UID unequal (the UID of adjacent data package isn't continuous)
    - 3: PID self check error
    - 4: Package length error

+ Request_Type: reserved, defined by user, value: 0~255

+ Err_UID: the UID of error package received previous, if haven't received UID, set the frame as 0.

***
<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Transmit%20Process(Master%20Side).jpg" alt="PID Frame" title="PID Frame" style="zoom: 100%;" />

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Transmit%20Process(Slave%20Side).jpg" alt="PID Frame" title="PID Frame" style="zoom: 100%;" />

```c
static const unsigned char crc_table[] =
{
    0x00,0x31,0x62,0x53,0xc4,0xf5,0xa6,0x97,0xb9,0x88,0xdb,0xea,0x7d,0x4c,0x1f,0x2e,
    0x43,0x72,0x21,0x10,0x87,0xb6,0xe5,0xd4,0xfa,0xcb,0x98,0xa9,0x3e,0x0f,0x5c,0x6d,
    0x86,0xb7,0xe4,0xd5,0x42,0x73,0x20,0x11,0x3f,0x0e,0x5d,0x6c,0xfb,0xca,0x99,0xa8,
    0xc5,0xf4,0xa7,0x96,0x01,0x30,0x63,0x52,0x7c,0x4d,0x1e,0x2f,0xb8,0x89,0xda,0xeb,
    0x3d,0x0c,0x5f,0x6e,0xf9,0xc8,0x9b,0xaa,0x84,0xb5,0xe6,0xd7,0x40,0x71,0x22,0x13,
    0x7e,0x4f,0x1c,0x2d,0xba,0x8b,0xd8,0xe9,0xc7,0xf6,0xa5,0x94,0x03,0x32,0x61,0x50,
    0xbb,0x8a,0xd9,0xe8,0x7f,0x4e,0x1d,0x2c,0x02,0x33,0x60,0x51,0xc6,0xf7,0xa4,0x95,
    0xf8,0xc9,0x9a,0xab,0x3c,0x0d,0x5e,0x6f,0x41,0x70,0x23,0x12,0x85,0xb4,0xe7,0xd6,
    0x7a,0x4b,0x18,0x29,0xbe,0x8f,0xdc,0xed,0xc3,0xf2,0xa1,0x90,0x07,0x36,0x65,0x54,
    0x39,0x08,0x5b,0x6a,0xfd,0xcc,0x9f,0xae,0x80,0xb1,0xe2,0xd3,0x44,0x75,0x26,0x17,
    0xfc,0xcd,0x9e,0xaf,0x38,0x09,0x5a,0x6b,0x45,0x74,0x27,0x16,0x81,0xb0,0xe3,0xd2,
    0xbf,0x8e,0xdd,0xec,0x7b,0x4a,0x19,0x28,0x06,0x37,0x64,0x55,0xc2,0xf3,0xa0,0x91,
    0x47,0x76,0x25,0x14,0x83,0xb2,0xe1,0xd0,0xfe,0xcf,0x9c,0xad,0x3a,0x0b,0x58,0x69,
    0x04,0x35,0x66,0x57,0xc0,0xf1,0xa2,0x93,0xbd,0x8c,0xdf,0xee,0x79,0x48,0x1b,0x2a,
    0xc1,0xf0,0xa3,0x92,0x05,0x34,0x67,0x56,0x78,0x49,0x1a,0x2b,0xbc,0x8d,0xde,0xef,
    0x82,0xb3,0xe0,0xd1,0x46,0x77,0x24,0x15,0x3b,0x0a,0x59,0x68,0xff,0xce,0x9d,0xac
};
```