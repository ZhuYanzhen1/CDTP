#include "ioctrl.h"
#include "decrypt.h"
void Receive_CallBack(unsigned char PID,unsigned char Data[])
{
		switch(PID)
		{
			case 0:
				//Receive 0 Package
				break;
			/******************/
		}
}
void Comm_SendChar(unsigned char Buf)
{
	
}
unsigned char Rcv_Flg = 0x00;
unsigned char Rcv_buf[32];
unsigned char RX_Counter=0x01;
void Comm_Rcv(unsigned char buf)
{
	if(buf == 0xff && Rcv_Flg == 1)
	{
		Rcv_Flg = 0;
		RX_Counter=1;
		Rcv_buf[11]=0xff;
		Comm_Received_CallBack((unsigned char *)&Rcv_buf);
	}
	else if(buf == 0xff && Rcv_Flg == 0)
	{
		Rcv_Flg = 1;
		RX_Counter=1;
		memset(&Rcv_buf,0x00,sizeof(Rcv_buf));
		Rcv_buf[0]=0xff;
	}
	else if(Rcv_Flg == 1)
	{
		Rcv_buf[RX_Counter] = buf;
		RX_Counter++;
	}
}
