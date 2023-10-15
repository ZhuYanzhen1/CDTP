/*****************************************************************************
    \file     decrypt.c
    \brief    Medium capacity transport protocol unpacking function Source File.
    \author   Lao·Zhu
    \version  V2.0.0
    \date     15. October 2023
******************************************************************************/

#include "decrypt.h"
#include "ioctrl.h"
#include "string.h"

/*!
    \brief  medium capacity transport protocol receive state variable
          0 idle state and waiting for start of package           \n
          1 receive status trying to receive a complete packet.   \n
          2 end status processing the received data
*/
static unsigned char mdtp_receive_status = 0;
/*!
    \brief  medium capacity transport protocol receive character counter
*/
static unsigned char mdtp_receive_number_counter = 0;
/*!
    \brief  medium capacity transport protocol receive buffer array
*/
static unsigned char mdtp_receive_data_buffer[10] = {0};

/*!
    \brief        medium capacity data transmission protocol unpacking handler
    \param[in]    data: data received from UART peripheral
    \retval       none
*/
void mdtp_receive_handler(unsigned char data) {
    /* data receiving finite state machine */
    switch (mdtp_receive_status) {
        case 0:
            /* judge whether the packet header is received */
            if (data == 0xAA) {
                /* enter the receive state */
                mdtp_receive_status = 1;

                /* clear receive array counter and buffer */
                mdtp_receive_number_counter = 0;
                memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            }
            break;

        case 1:
            /* judge whether the end of the packet is mistakenly recognized as the header */
            if (data == 0xAA && mdtp_receive_number_counter != 0) {
                /* an unexpected data had been received */
                /* reset to receive start of package state */
                mdtp_receive_status = 0;

                /* clear receive array counter and buffer */
                mdtp_receive_number_counter = 0;
                memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            } else if (data != 0xAA) {
                /* judge whether the reception is completed or the error data is received */
                if (mdtp_receive_number_counter != 10) {
                    /* receive the data into the array in turn */
                    mdtp_receive_data_buffer[mdtp_receive_number_counter] = data;
                    mdtp_receive_number_counter = mdtp_receive_number_counter + 1;
                    if (mdtp_receive_number_counter == 10)
                        mdtp_receive_status = 2;
                }
            }
            break;

        case 2:
            if (data == 0xAA) {
                /* reset to receive start of package state */
                mdtp_receive_status = 0;

                /* verify whether the pid byte is correct*/
                if ((mdtp_receive_data_buffer[0] >> 4) == (~mdtp_receive_data_buffer[0] & 0x0f)) {
                    static unsigned char tmp_rcv_buffer[8] = {0}, adj_counter = 0;
                    /* judge whether the adjust frame is 0xAA */
                    if (mdtp_receive_data_buffer[8] == 0xA5 && mdtp_receive_data_buffer[9] == 0x80)
                        /* set adjust frame to with 0xAA */
                        mdtp_receive_data_buffer[9] = 0xAA;
                    /* traverse the data byte to be adjusted */
                    for (adj_counter = 0; adj_counter < 8; ++adj_counter) {
                        /* judge whether the adjustment bit is 1 */
                        if (((mdtp_receive_data_buffer[9] >> adj_counter) & 0x01) == 0x01)
                            /* fill the data byte with 0xAA */
                            tmp_rcv_buffer[adj_counter] = 0xAA;
                        else
                            /* copy data directly to the receiving array */
                            tmp_rcv_buffer[adj_counter] = mdtp_receive_data_buffer[adj_counter + 1];
                    }
                    /* call user callback function to complete the next step */
                    mdtp_callback_handler(mdtp_receive_data_buffer[0] >> 4, tmp_rcv_buffer);
                }
            } else {
                /* an unexpected data had been received */
                /* reset to receive start of package state */
                mdtp_receive_status = 0;

                /* clear receive array counter and buffer */
                mdtp_receive_number_counter = 0;
                memset(mdtp_receive_data_buffer, 0x00, sizeof(mdtp_receive_data_buffer));
            }
            break;
        default: break;
    }
}
