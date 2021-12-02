/*****************************************************************************
    \file     ioctrl.c
    \brief    Generic single-byte send/receive functions Source File.
    \author   Lao·Zhu
    \version  V1.0.3
    \date     3. December 2021
******************************************************************************/

#include "ioctrl.h"
#include "decrypt.h"

/*!
    \brief        user callback function for unpacking completion of medium capacity transport protocol
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \retval       none
*/
void mdtp_callback_handler(unsigned char pid, unsigned char *data) {
}

/*!
    \brief        general single byte sending function
    \param[in]    data: data byte to send
    \retval       none
*/
void common_sendbyte(unsigned char data) {
}

/*!
    \brief        general single byte receiving function
    \param[in]    data: data byte received
    \retval       none
*/
void common_receivebyte(unsigned char data) {
    mdtp_receive_handler(data);
}
