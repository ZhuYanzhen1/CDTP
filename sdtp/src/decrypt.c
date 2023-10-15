/*****************************************************************************
    \file     decrypt.c
    \brief    Small capacity transport protocol unpacking function Source File.
    \author   Lao·Zhu
    \version  V2.0.0
    \date     15. October 2023
******************************************************************************/

#include "decrypt.h"
#include "ioctrl.h"

static unsigned char receive_buffer[3];

/*!
    \brief        small capacity data transmission protocol unpacking handler
    \param[in]    data: data received from general receive function
    \retval       none
*/
void sdtp_receive_handler(unsigned char data) {
    /* data receiving finite state machine */
    switch (((data & 0xC0) >> 6)) {
        case 0x00:
            /* separate the first two bits of the byte to obtain valid data */
            receive_buffer[0] = ((data & 0x3F) << 2);
            break;
        case 0x01:
            /* separate the first two bits of the byte to obtain valid data */
            receive_buffer[0] |= ((data & 0x30) >> 4);
            receive_buffer[1] = ((data & 0x0F) << 4);
            break;
        case 0x02:
            /* separate the first two bits of the byte to obtain valid data */
            receive_buffer[1] |= ((data & 0x3C) >> 2);
            receive_buffer[2] = ((data & 0x03) << 6);
            break;
        case 0x04:
            /* separate the first two bits of the byte to obtain valid data */
            receive_buffer[2] |= (data & 0x3F);
            /* call user callback function to complete the next step */
            sdtp_callback_handler(receive_buffer);
            break;
    }
}
