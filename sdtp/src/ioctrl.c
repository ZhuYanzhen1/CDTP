/*****************************************************************************
    \file     ioctrl.c
    \brief    Generic single-byte send/receive functions Source File.
    \author   Lao·Zhu
    \version  V2.0.0
    \date     15. October 2023
******************************************************************************/

#include "ioctrl.h"
#include "decrypt.h"

/*!
    \brief        user callback function for unpacking completion of small capacity transport protocol
    \param[in]    data: received data array of size 3 bytes
    \retval       none
*/
void sdtp_callback_handler(unsigned char *data) {

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
    sdtp_receive_handler(data);
}
