# 大容量数传协议

[Switch to English](https://github.com/ZhuYanzhen1/CDTP/blob/master/Large%20Capacity/README.md)

***

### 适用场景:
+ 基于半双工传输协议

+ 从机向主机进行大容量数据传输

+ 主机向从机进行小容量数据传输

+ 需要稳定的重新传输和应答机制

+ 需要多样化的数据校验方式

+ 需要支持突发传输

***

### 说明：

这是一个可变长度传输协议，最大数据长度为14字节，最小数据长度为3字节。基本的包元素含有起始帧，包标识符，结束帧。通信建立前由主设备起握手包，在每一帧数据或者控制包传输后，需要由从设备进行应答，每帧数据占用一字节（八个二进制位）。
***
<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Type%20Corresponding%20Package%20Content_cn.jpg" alt="PID Corresponding PC" title="PID Corresponding PC"  />

| 包功能（包名） |                            包说明                            |
| :------------: | :----------------------------------------------------------: |
|     握手包     | 通信开始的标志，由主设备首先传出，之后从设备用相同的包进行应答。 |
|     应答包     |              从设备为了应答每一帧数据或者控制包              |
|    全填充包    |         此包代表了每一帧都由0xff构成的数据域的数据包         |
|     终止包     |                        通信结束的标志                        |
| ~~重设UID包~~  |                     ~~将UID位设为0x00~~                      |
|     重传包     |             要求另外的设备重新传输并替代错误的包             |
|     请求包     | 由主设备发送请求包到从设备，从设备需要传输相应的数据给主设备 |
| DATA0/DATA1 包 | 当需要传输大容量数据的时候，DATA0包和DATA1包应该要互相交替使用 |
|     空闲包     |        保留包用于较少的数据或者命令传输，由用户自定义        |

##### 帧说明:
+ 帧头：值为0xff的帧

+ 桢尾：值为0xff的帧

+ 独立ID：每一帧数据的特殊标识

+ 校验帧：从PID到CRC的循环冗余校验

```c
unsigned char calculate_crc8(unsigned char *ptr, unsigned char len) 
{
    unsigned char  crc_result = 0x00;
    while (len--)
    {
        crc_result = crc_table[crc ^ *ptr++];
        //crc表在这个README文件的结尾
    }
    return (crc);
}
```

+ 调整帧：调整数据区以确保数据帧中不含有0xff。如果含有，就会设置相对应的位用于调整帧节，最后清除该数据帧为0x00

  调整方式在下图中说明
 <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Adjust%20Frame_cn.jpg" alt="Adjust Frame" title="Adjust Frame" style="zoom: 50%;" />

+ 包标识符：占用四个位，该值可取0到15，低四位与高四位位反。

  自我校验方式在以下图中说明
  <img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/PID%20Frame_cn.jpg" alt="PID Frame" title="PID Frame" style="zoom: 50%;" />

+ 出错类型：先前接收到的错误包的类型
  
    - 0：丢失帧头或帧尾（出现两个相邻的0xff帧）
    - 1: CRC 校验值与接收的值不等同
    - 2: 数据包相应独立ID与接收的值不相同（相邻数据包的UID不连续）
    - 3: 包标识符自我校验出错
    - 4: 包长度出错

+ 请求类型: 预留, 由用户自定义，范围0~254

+ 出错UID: 之前收到错误包的UID，如果没有收到UID，该值应为0.

***
<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Transmit%20Process(Master%20Side)_cn.jpg" alt="PID Frame" title="PID Frame" style="zoom: 100%;" />

<img src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Transmit%20Process(Slave%20Side)_cn.jpg" alt="PID Frame" title="PID Frame" style="zoom: 100%;" />

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