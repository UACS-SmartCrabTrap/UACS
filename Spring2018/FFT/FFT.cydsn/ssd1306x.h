/**************
 * FFT on PSoC4
 **************
 * A project by @KaiserHaz
 * 
 * Extra display libraries. Extension to ssd1306.h, specifically for eq display
 * 
 */

#ifndef _SSD1306X_H_
#define _SSD1306X_H_

/** Include previous lib **/
#include "ssd1306.h"
    
/** Channel fixed vars **/
#define _OLED_EQ_CHAN_CNT_ 16
#define _OLED_EQ_CHAN_MULT_ 8
    
/** Channel offsets **/
#define _OLED_EQ_FBUF_OFF_ 0
#define _OLED_EQ_ACT_OFF_ 1
#define _OLED_EQ_BBUF_OFF_ 7

/** Channel defines **/
#define _OLED_EQ_CHAN_1_ 0
#define _OLED_EQ_CHAN_2_ 1
#define _OLED_EQ_CHAN_3_ 2
#define _OLED_EQ_CHAN_4_ 3
#define _OLED_EQ_CHAN_5_ 4
#define _OLED_EQ_CHAN_6_ 5
#define _OLED_EQ_CHAN_7_ 6
#define _OLED_EQ_CHAN_8_ 7
#define _OLED_EQ_CHAN_9_ 8
#define _OLED_EQ_CHAN_10_ 9
#define _OLED_EQ_CHAN_11_ 10
#define _OLED_EQ_CHAN_12_ 11
#define _OLED_EQ_CHAN_13_ 12
#define _OLED_EQ_CHAN_14_ 13
#define _OLED_EQ_CHAN_15_ 14
#define _OLED_EQ_CHAN_16_ 15

/** Channel structure **/
typedef struct {
    int16_t _oled_eq_chan_num;                             // Channel number
    int16_t _oled_eq_chan_mag;                             // Channel magnitude
} oled_eq_chan;

/** Global vars **/
extern oled_eq_chan* _oled_eq_chan_tab_;                   // Channel array

/** Methods **/
void oled_draw_channel0( int16_t chan, int16_t mag, uint16_t color );
void oled_draw_channel1( int16_t chan, int16_t mag, uint16_t color );
void oled_draw_channel2( oled_eq_chan chan, uint16_t color );
void oled_eq_chan_init();
void oled_update_channel_mag( int16_t chan, int16_t mag );
void oled_update_channels_mag( int16_t* mag );
void oled_update_channel();
double oled_normalize_channel_mag( double mag );
void oled_normalize_channels_mag( double* mag, int16_t* nmag );
//int16_t oled_normalize_channel_mag( int16_t mag );
//void oled_normalize_channels_mag( int16_t* mag, int16_t* nmag );

#endif

/* [] END OF FILE */
