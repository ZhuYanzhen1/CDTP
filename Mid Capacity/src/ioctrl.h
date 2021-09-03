//
// Created by Lao·Zhu on 2021/9/4.
//

#ifndef _IOCTRL_H_
#define _IOCTRL_H_

void mdtp_callback_handler(unsigned char pid, unsigned char *data);
void common_sendbyte(unsigned char Buf);
void common_receivebyte(unsigned char buf);

#endif
