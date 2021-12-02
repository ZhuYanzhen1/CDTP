/*****************************************************************************
    \file     encrypt.h
    \brief    Medium capacity transport protocol packing function Header File.
    \author   Lao·Zhu
    \version  V1.0.3
    \date     3. December 2021
******************************************************************************/

#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

void mdtp_data_transmit(unsigned char pid, const unsigned char *data);

#endif  // _ENCRYPT_H_
