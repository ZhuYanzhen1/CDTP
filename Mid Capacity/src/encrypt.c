//
// Created by Lao·Zhu on 2021/9/4.
//

#include "encrypt.h"
#include "ioctrl.h"

/*!
    \brief      medium capacity data transmission protocol packing function
    \param[in]    pid: medium capacity transport protocol package id
    \param[in]    data: received data array of size 8 bytes
    \param[out]   none
    \retval     none
*/
void mdtp_data_transmit(unsigned char pid, const unsigned char *buffer) {
    unsigned char temp_buf[12] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0xff};
    unsigned char mdtp_pack_counter;
    /* traverse the array to determine whether there are bytes to be adjusted */
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 8; mdtp_pack_counter++) {
        /* judge whether this byte need to be adjusted */
        if (buffer[mdtp_pack_counter] == 0xff) {
            temp_buf[2 + mdtp_pack_counter] = 0x00;
            /* modify the corresponding bit of the adjustment byte */
            temp_buf[10] = (temp_buf[10] | (1 << mdtp_pack_counter));
        } else
            /* copy data directly to transmit buffer array */
            temp_buf[2 + mdtp_pack_counter] = buffer[mdtp_pack_counter];
    }
    /* judge whether the package is all 0xff */
    if (temp_buf[10] == 0xff)
        temp_buf[10] = temp_buf[2] = 0xa5;
    /* load self checking packet id byte */
    temp_buf[1] = pid << 4 | ((~pid) & 0x0f);
    /* traverse the buffer array and send all bytes through UART0 */
    for (mdtp_pack_counter = 0; mdtp_pack_counter < 12; mdtp_pack_counter++) {
        /* transmit single byte through UART0 */
        common_sendbyte(temp_buf[mdtp_pack_counter]);
    }
}
