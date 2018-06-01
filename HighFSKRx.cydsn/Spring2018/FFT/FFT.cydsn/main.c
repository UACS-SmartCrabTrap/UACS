/**************
 * FFT on PSoC4
 **************
 * A project by @KaiserHaz
 * 
 * Description:
 * ************
 *  
 *  This project aims to demonstrate an FFT algorithm running on Cortex-M0.
 *  In order to make things interesting, we will use it in the case of an audio
 *   spectrum visualizer. It will be displayed on an OLED screen (SSD1306).
 *  The FFT algorithm is based (most-probably) on Sorensen et al. (RFFT).
 *  Initially I planned to implement an FFT on hardware using PSoC, but the PSoC 4200
 *   I have does not contain enough resources to be able to do that, so I had to
 *   make do with a software implementation.
 *  But hey, at least I could make a (semi-)complete processing chain.
 *
 * Details:
 * ********
 *
 * Signal input : Differential Mono (v1.0)
 * FFT Length   : 16                (v1.0)
 * FFT Algorithm: Radix-2 DIT FFT   (vSandbox)
 * 
 * Libraries:
 * **********
 *
 * Several 'libraries' (actually they're PSoC projects) have been used in this project, namely:
 * * 64-point FFT library (http://www.cypress.com/comment/240586#comment-240586) (vSandbox)
 * * OLED Library for I2C (https://github.com/derkst/Cypress-PSOC-OLED)          (v1.0)
 *
 * Credits to these people for working hard and developing something useful for the community.
 * 
 */

/** Includes **/
#include <project.h>
#include <stdlib.h>
#include <math.h>                                          // Put m in settings
#include "ssd1306x.h"

/** Constant defines **/
#define _FFT_PI_ 3.14159
#define _FFT_LEN_ 16
#define _OLED_DISP_ADDR_ 0x3C // 011110+SA0+RW - 0x3C or 0x3D

/** Global vars **/
extern oled_eq_chan* _oled_eq_chan_tab_;

int16_t samples[_FFT_LEN_] = /*{ 0, 8, 14, 18, 20, 18, 14, 8,
                               0, -8, -14, -18, -20, -18, -14, -8 }; // Sinusoid*/
                             { 0, 2, 3, 5, 6, 8, 10,
                               1, 3, 4, 6, 8, 9, 1, 2, 4 }; // Sawtooth

int revsamples[_FFT_LEN_];

int16 real0[_FFT_LEN_];		/* Array to hold the real value of samples */
int16 img0[_FFT_LEN_];			/* Array to hold the img value of samples */

int16 real1[_FFT_LEN_];		/* Array to hold the real value of samples */
int16 img1[_FFT_LEN_];			/* Array to hold the img value of samples */

int16 twiddlereal[_FFT_LEN_];	/* Array to hold the real value of twiddle factor */
int16 twiddleimg[_FFT_LEN_];	/* Array to hold the img value of twiddle factor */

int16 interreal[_FFT_LEN_];	/* Array to hold the real product of intermediate multiplication */
int16 interimg[_FFT_LEN_];		/* Array to hold the img product of intermediate multiplication */

float product;

/** Complex number structure **/
typedef struct { double _real; double _imag; } complex;

/** Twiddle factor function **/
complex twiddle_factor( uint8_t k, uint8_t n, uint8_t N ){
    
    complex tf = { ._real=1.0, ._imag=0.0 };
    
    // Case k&n = 0: no need to calculate anything, just return
    if(k && n){
        
        tf._real = cos(2.0*_FFT_PI_*k*n/N);
        tf._imag = (-1)*sin(2.0*_FFT_PI_*k*n/N);

    }
    
    return tf;
    
}

int main(){
    
    // Enable interrupts
    
    CyGlobalIntEnable;
    
    // OLED start routine
    
    I2COLED_Start();                                       // Start

    display_init(_OLED_DISP_ADDR_);                        // Initialize display
                                                           //  with address
    
    oled_eq_chan_init();                                   // Initialize
                                                           //  equalizer
                                                           //  display
    
    uint8 i, j; 
	uint8 revi;
	uint8 localcounter;
	
    /* Calculate the twiddle factors */
	for(i=0; i<(_FFT_LEN_/2); i++)
	{
		product = cos(2 * _FFT_PI_ * i / _FFT_LEN_);
        twiddlereal[i] = (int16) (product *256);           // Possibly a gain
		product = sin(2 * _FFT_PI_ * i / _FFT_LEN_);
		twiddleimg[i] = (int16)(product *(-256));
	}
	
    /* First phase of FFT is arranging the input samples in bit reversed format */
	for(i=0; i< _FFT_LEN_; i++)
	{
        revi = (((i >> 1) & 0x5) | ((i & 0x5) << 1));
        revi = (((revi >> 2) & 0x3) | ((revi & 0x3) << 2));
		
		revsamples[i] = samples[revi];
	}
	
	for(;;)
	{
	
    	/* First stage of FFT radix 2 implementation */
    	
    	for(i=0; i< _FFT_LEN_; )
    	{
    		real0[i] = revsamples[i] + revsamples[i+1];
    		real0[i+1] = revsamples[i] - revsamples[i+1];
    		i = i+2;
    	}
    	
    	/* Second stage of FFT radix 2 implementation */
    	for(i=0; i<_FFT_LEN_; )
    	{
    		real1[i] = real0[i] + real0[i+2];
    		img1[i] = img0[i] + img0[i+2];
    		
    		real1[i+1] = real0[i+1] + real0[i+3];
    		img1[i+1] = img0[i] - img0[i+3];
    		
    		real1[i+2] = real0[i] - real0[i+2];
    		img1[i+2] = img0[i] + img0[i+2];
    		
    		real1[i+3] = real0[i+1] + real0[i+3];
    		img1[i+3] = img0[i+1] + img0[i+3];
    		
    		i = i + 4;
    	}
    	
    	/* Third stage of FFT radix 2 implementation */
    	for(i=0; i<_FFT_LEN_; )
    	{
            // Compute product of twiddle with data
    		for(j=0; j<4; j++)
    		{
    			interreal[j] = (real1[i + j + 4] * twiddlereal[2*j])>>8;
    			interimg[j] = (img1[i + j + 4] * twiddleimg[2*j])>>8;
    		}
    		
    		// Non-returned part/Non-looped part
    		for(localcounter=0; localcounter<4; localcounter++)
    		{
    			real0[i + localcounter] = real1[i + localcounter] + interreal[localcounter];
    			img0[i + localcounter] = img1[i + localcounter] + interimg[localcounter];
    		}
    		
            // Returned part/Looped part
    		for(localcounter = 4; localcounter<8; localcounter++)
    		{
    			real0[i + localcounter] = real1[i + localcounter - 4] - interreal[localcounter % 4];
    			img0[i + localcounter] = img1[i + localcounter - 4] - interimg[localcounter % 4];
    		}
            
    		i = i+8;
    	}
    	
    	/* Fourth stage of FFT radix 2 implementation */
    	for(i=0; i< _FFT_LEN_;  )
    	{
    		// Compute product of twiddle with data
    		for(j=0; j<8; j++)
    		{
    			interreal[j] = (real0[i + j + 8] * twiddlereal[j])>>8;
    			interimg[j] = (img0[i + j + 8] * twiddleimg[j])>>8;
    		}
    		
    		// Non-returned part/Non-looped part
    		for(localcounter = 0; localcounter<8; localcounter++)
    		{
    			real1[i + localcounter] = real0[i + localcounter] + interreal[localcounter];
    			img1[i + localcounter] = img0[i + localcounter] + interimg[localcounter];
    		}
    		
            // Returned part/Looped part
    		for(localcounter = 8; localcounter<16; localcounter++)
    		{
    			real1[i + localcounter] = real0[i + localcounter - 8] - interreal[localcounter % 8];
    			img1[i + localcounter] = img0[i + localcounter - 8] - interimg[localcounter % 8];
    		}
            
    		i = i+16;
    	}
        
        double fft_abs[_FFT_LEN_];
        
        for(i=0; i<_FFT_LEN_; i++)
            fft_abs[i] = sqrt(real1[i]*real1[i] + img1[i]*img1[i]);
        
        oled_normalize_channels_mag(fft_abs, real1);
        
        oled_update_channels_mag(real1);
        
        oled_update_channel();
        
        CyDelay(41);
        
    }
}

/* [] END OF FILE */