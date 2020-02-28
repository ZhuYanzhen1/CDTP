#include "decrypt.h"
#include "ioctrl.h"
unsigned char Temp_Buf[3];
void Comm_Received_CallBack(unsigned char buf)
{
	switch(((buf & 0xc0) >> 6))
	{
		case 0x00:
			Temp_Buf[0] = ((buf & 0x3f) << 2);
			break;
		case 0x01:
			Temp_Buf[0] |= ((buf & 0x30) >> 4);
			Temp_Buf[1] = ((buf & 0x0f) << 4);
			break;
		case 0x02:
			Temp_Buf[1] |= ((buf & 0x3c) >> 2);
			Temp_Buf[2] = ((buf & 0x03) << 6);
			break;
		case 0x04:
			Temp_Buf[2] |= (buf & 0x3f);
			Receive_CallBack(Temp_Buf);
		break;
	}
}
