//
// Created by Lao·Zhu on 2021/9/4.
//

#include "ioctrl.h"
#include "decrypt.h"

/*!
    \brief        user callback function for unpacking completion of small capacity transport protocol
    \param[in]    data: received data array of size 3 bytes
    \param[out]   none
    \retval       none
*/
void sdtp_callback_handler(unsigned char *data) {

}

/*!
    \brief        general single byte sending function
    \param[in]    data: data byte to send
    \param[out]   none
    \retval       none
*/
void common_sendbyte(unsigned char data) {

}

/*!
    \brief        general single byte receiving function
    \param[in]    data: data byte received
    \param[out]   none
    \retval       none
*/
void common_receivebyte(unsigned char data) {
    sdtp_receive_handler(data);
}
