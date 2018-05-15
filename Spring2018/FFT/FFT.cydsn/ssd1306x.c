/**************
 * FFT on PSoC4
 **************
 * A project by @KaiserHaz
 * 
 * Extra display libraries. Extension to ssd1306.h. Function implementations
 * 
 */

#include <project.h>
#include <stdlib.h>
#include <math.h>
#include "ssd1306x.h"

oled_eq_chan* _oled_eq_chan_tab_;

/**
 * Method : oled_draw_channel0
 * Args   : int16_t chan  : Channel number
 *          int16_t mag   : Magnitude
 *          uint16_t color: Display color
 * Returns: -
 * Descr  : Draws channel chan with the given magnitude mag. Standalone ver
 *
 */
void oled_draw_channel0( int16_t chan, int16_t mag, uint16_t color ){
    
    uint8_t ii = 0;
    
    display_clear();
    
    for( ii = 0 ; ii < mag ; ii++ ){
        gfx_drawLine( (chan*_OLED_EQ_CHAN_MULT_)+_OLED_EQ_ACT_OFF_, ii,
                      (chan*_OLED_EQ_CHAN_MULT_)+_OLED_EQ_BBUF_OFF_-_OLED_EQ_ACT_OFF_, ii, color );
    }
    
    display_update();
    
}

/**
 * Method : oled_draw_channel1
 * Args   : int16_t chan  : Channel number
 *          int16_t mag   : Magnitude
 *          uint16_t color: Display color
 * Returns: -
 * Descr  : Draws channel chan with the given magnitude mag
 *
 */
void oled_draw_channel1( int16_t chan, int16_t mag, uint16_t color ){
    
    uint8_t ii = 0;
    
    for( ii = 0 ; ii < mag ; ii++ ){
        gfx_drawLine( (chan*_OLED_EQ_CHAN_MULT_)+_OLED_EQ_ACT_OFF_, ii,
                      (chan*_OLED_EQ_CHAN_MULT_)+_OLED_EQ_BBUF_OFF_-_OLED_EQ_ACT_OFF_, ii, color );
    }
    
}

/**
 * Method : oled_draw_channel2
 * Args   : oled_eq_chan chan  : Channel structure
 *          uint16_t color     : Display color
 * Returns: -
 * Descr  : Draws channel chan. Just calls the above method really
 *
 */
void oled_draw_channel2( oled_eq_chan chan, uint16_t color ){
    oled_draw_channel1(chan._oled_eq_chan_num,
                       chan._oled_eq_chan_mag, color);
}

/**
 * Method : oled_eq_chan_init
 * Args   : -
 * Returns: -
 * Descr  : Initializes channel structure array
 *
 */
void oled_eq_chan_init(){
    
    uint8_t ii;
    
    _oled_eq_chan_tab_ = (oled_eq_chan*) malloc(_OLED_EQ_CHAN_CNT_*sizeof(oled_eq_chan));
    
    for(ii = 0; ii < _OLED_EQ_CHAN_CNT_; ii++){
        
        _oled_eq_chan_tab_[ii]._oled_eq_chan_num = ii;     // Should be consts
                                                           //  here but meh...
        _oled_eq_chan_tab_[ii]._oled_eq_chan_mag = 1;
    
        oled_draw_channel2(_oled_eq_chan_tab_[ii], WHITE);
        
    }
    
    display_update();
    
}

/**
 * Method : oled_update_channel_mag
 * Args   : int16_t chan
 *          int16_t mag
 * Returns: -
 * Descr  : Update channel magnitude for specified channel
 *
 */
void oled_update_channel_mag( int16_t chan, int16_t mag ){
    
    _oled_eq_chan_tab_[chan]._oled_eq_chan_mag = mag;      // Hardcoded 8 to
                                                           //  save process
                                                           //  time?
    
}

/**
 * Method : oled_update_channels_mag
 * Args   : int16_t chan
 *          int16_t mag
 * Returns: -
 * Descr  : Update all channel magnitudes
 *
 */
void oled_update_channels_mag( int16_t* mag ){
    
    uint8_t ii;
    
    for( ii = 0; ii < _OLED_EQ_CHAN_CNT_; ii++ ){
        
        oled_update_channel_mag(ii, (int16_t)mag[ii]);
        
    }
    
}

/**
 * Method : oled_update_channel
 * Args   : -
 * Returns: -
 * Descr  : Update channel display. Basically redraws the whole display
 *
 */
void oled_update_channel(){
    
    uint8_t ii;
    
    display_clear();
    
    for( ii = 0; ii < _OLED_EQ_CHAN_CNT_; ii++ ){
        
        oled_draw_channel2(_oled_eq_chan_tab_[ii], WHITE);
        
    }
    
    display_update();
    
}

/**
 * Method : oled_normalize_channel_mag
 * Args   : double mag
 * Returns: double
 * Descr  : Normalize channel magnitude to follow a 20 log scale
 *
 */
double oled_normalize_channel_mag( double mag ){
    
    double res;
    
    res = 20*log(mag);
    
    return res;
    
}

/**
 * Method : oled_normalize_channels_mag
 * Args   : double* mag
 *          int16_t* nmag 
 * Returns: -
 * Descr  : Normalize all channel magnitudes and log-limits them
 *
 */
void oled_normalize_channels_mag( double* mag, int16_t* nmag ){
    
    uint8 ii;
    double max = 0;
    
    for(ii=0; ii<_OLED_EQ_CHAN_CNT_; ii++){
        mag[ii] = oled_normalize_channel_mag(mag[ii]);
    }
    for(ii=0; ii<_OLED_EQ_CHAN_CNT_; ii++){
        max = (max < mag[ii]) ? mag[ii]:max;
    }
    for(ii=0; ii<_OLED_EQ_CHAN_CNT_; ii++){
        mag[ii] = (mag[ii]/max)*((double)gfx_height());
    }
    for(ii=0; ii<_OLED_EQ_CHAN_CNT_; ii++){
        nmag[ii] = (int16_t) mag[ii];
    }
    
}

/* [] END OF FILE */
