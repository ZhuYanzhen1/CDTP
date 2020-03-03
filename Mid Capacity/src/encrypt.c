#include "encrypt.h"
void Send_Data(unsigned char pid, unsigned char Data[8])
{
	unsigned char temp_buf[12];
	unsigned char cnt = 0;
	memset(temp_buf,0x00,sizeof(temp_buf));
	temp_buf[0] =  0xff;										//set start of frame
	temp_buf[10] = 0x00;										//initialize adjust frame
	for(cnt = 0;cnt < 8;cnt++)							//copy data and adjust
	{
                if(Data[cnt] == 0xff)									//if data equal 0xff, mark it
		{
			temp_buf[2 + cnt] = 0x00;
			temp_buf[10] = (temp_buf[10] | (1 << cnt));
		}
		else
                        temp_buf[2 + cnt] = Data[cnt];
	}
	temp_buf[1] = pid<<4 | ((~pid) & 0x0f);	//set pid and check
	temp_buf[11] = 0xff;										//set end of frame
	for(cnt = 0;cnt < 12;cnt++)
		Comm_SendChar(temp_buf[cnt]);
}
