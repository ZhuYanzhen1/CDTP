#ifndef _IOCTRL_H_
#define _IOCTRL_H_
void Receive_CallBack(unsigned char PID,unsigned char Data[]);
void Comm_SendChar(unsigned char Buf);
void Comm_Rcv(unsigned char buf);
#endif
