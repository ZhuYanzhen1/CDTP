/*****************************************************************************
    \file     ioctrl.h
    \brief    Generic single-byte send/receive functions Header File.
    \author   Lao·Zhu
    \version  V1.0.3
    \date     3. December 2021
******************************************************************************/

#ifndef _IOCTRL_H_
#define _IOCTRL_H_

void mdtp_callback_handler(unsigned char pid, unsigned char *data);
void common_sendbyte(unsigned char data);
void common_receivebyte(unsigned char data);

#endif  // _IOCTRL_H_
