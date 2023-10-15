/*****************************************************************************
    \file     ioctrl.h
    \brief    Generic single-byte send/receive functions Header File.
    \author   Lao·Zhu
    \version  V2.0.0
    \date     15. October 2023
******************************************************************************/

#ifndef _IOCTRL_H_
#define _IOCTRL_H_

void sdtp_callback_handler(unsigned char *data);
void common_sendbyte(unsigned char data);
void common_receivebyte(unsigned char data);

#endif  // _IOCTRL_H_
