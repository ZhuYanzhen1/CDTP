#include "encrypt.h"
void Send_Data(unsigned char Data[3])
{
	unsigned char temp_buf[4];
	unsigned char cnt;
        temp_buf[0] = (Data[0] >> 2);
        temp_buf[1] = (0x01 << 6) | ((Data[0] & 0x03) << 4) | (Data[1] >> 4);
        temp_buf[2] = (0x01 << 7) | ((Data[1] & 0x0f) << 2) | (Data[2] >> 6);
        temp_buf[3] = (0x03 << 6) | (Data[2] & 0x3f);
	for(cnt = 0; cnt < 4;cnt++)
		Comm_SendChar(temp_buf[cnt]);
}
