/*included files*/
#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

/*definitions*/
#define TX_ENCODING 0xFFFF //Encoding we expect to receive from Tx
#define TX_DECODING 0x0001 //Decoding we expect to receive from Tx

#define ONE_THRESHOLD 7 //If sig is high for 7 of LEVEL_COUNTER_CHECK_BIT_TIME
                        // samples then we consider the incoming signal a 1.
#define LEVEL_COUNTER_CHECK_BIT_TIME 10 //Number of checks we make on input
                                        // level to determine if we get a high 
                                        // or low signal. Each check occurs at
                                        // 0.05s increments.
#define DATA_LENGTH 7 //The length of the data we expect to receive minus 1.
#define DECODE_LENGTH 15 //The length of the decode we expect to receive minus
                         // 1.
#define ONE  0x0001
#define ZERO 0x0000

#define TRUE  0x01
#define FALSE 0x00

#define NOT_LOOKING_FOR_DATA 0   //This block of definitions is used for flags.
#define NOT_LOOKING_FOR_DECODE 0
#define NOT_LOOKING_FOR_ENCODE 0
#define LOOK_FOR_DATA 1
#define LOOK_FOR_DECODE 1
#define LOOK_FOR_ENCODE 1

/*function prototypes*/
CY_ISR_PROTO(LevelCount);

/*global variables*/
static uint32 levelCounter = ZERO;
static uint32 zeroCount = ZERO; 
static uint32 oneCount = ZERO; 
static uint32 currentBit = ZERO;
static uint32 dataCount = ZERO;
static uint32 data = ZERO;
static uint32 crabs = ZERO;
//FLAGS
static uint8 lcdFlagEncode = FALSE;
static uint8 lcdFlagData = FALSE;
static uint8 lcdFlagDecode = FALSE;
static uint8 encodeFlag = LOOK_FOR_ENCODE;
static uint8 dataFlag = NOT_LOOKING_FOR_DATA;
static uint8 decodeFlag = NOT_LOOKING_FOR_DECODE;
static uint8 decodeWrong = FALSE;

/*
 * function: main()
 * parameters: none
 * returns: should never return
 * description:
 */
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /*Hardware block initialization*/
    BPF_Comp_Start();
    ShiftReg_Start();
    PGA_Start() ; 
    OutComp_Start();
    LevelCount_Start();
    LevelCountISR_StartEx(LevelCount);
    LCD_Char_Start();
    
    char OutputString[12];
    char display[12];
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u);
    LCD_Char_PrintString(display);

    for(;;)
    {
        if(lcdFlagEncode == 1){
            LCD_Char_ClearDisplay();
            LCD_Char_PrintString("0xFFFF pre-fix");
            lcdFlagEncode = 0;
        }else if(lcdFlagData == 1){
            sprintf(OutputString, "%i", crabs);
            LCD_Char_ClearDisplay();
            LCD_Char_Position(0u,0u);
            LCD_Char_PrintString(OutputString);
            LCD_Char_PrintString(" crabs");
            dataFlag = 0;
            lcdFlagData = 0;
        }else if(lcdFlagDecode == 1){
            LCD_Char_Position(1u,0u);
            char8 displayG[] = "good";
            LCD_Char_PrintString(displayG);
            dataFlag = 0;
            lcdFlagDecode = 0;
        }else if(decodeWrong == 1){
            LCD_Char_Position(1u,0u);
            char8 displayB[] = "bad";
            LCD_Char_PrintString(displayB);
            decodeWrong = FALSE;
        }
    } //end for(;;)
} //end main()
    
/*
 * function: CY_ISR(LevelCount)
 * parameters: None
 * return: None
 * description: This function interrupts every 0.05s and checks the current
 *  input level. If the input level is high for 7 out of 10 checks then we
 *  consider the input bit a 1, otherwise it is a 0.
 *      This function also checks for an encoding, data, and a decoding. The
 * function waits for 16 consecutive 1 bits to determine if it received an
 * encoding. After it successfully gets the encoding it checks for data by
 * assuming the next 8 bits is the data. Lastly, it checks the decoding by
 * assuming the next 16 bits after the data is the decoding and will determine
 * if the data is corrupt by checking if it matches our expected decoding.
 */
CY_ISR(LevelCount){
    char OutputString[12];
    
    levelCounter++; //Increments every 50ms
    
    //Checks inputs level to determine a high or low level
    if(OutComp_GetCompare() != ZERO){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    //debouncing every 0.5s, with a check of 7/10 hits
    //After checking input levels for half a second, we check if we received
    // our encoding, data, or decoding
    if(levelCounter == LEVEL_COUNTER_CHECK_BIT_TIME){
        
        //If input level is high for at least 7 of the times we poll it during
        // a 0.5s interval, we consider it a 1, otherwise it is a 0.
        if(oneCount >= ONE_THRESHOLD){
            currentBit = ONE;
        }else{
            currentBit = ZERO; 
        }
        zeroCount = ZERO;
        oneCount = ZERO;
        
        //Current data values
        dataCount++;
        data = data << 1;
        data = data | currentBit;
        
        sprintf(OutputString, "%i", data);
        LCD_Char_ClearDisplay();
        LCD_Char_PrintString(OutputString);
        
        //Check for encoding
        if((data == TX_ENCODING) && (encodeFlag == LOOK_FOR_ENCODE)){
            CountOut_Write(1);
            dataCount = ZERO;
            data = ZERO;
            dataFlag = LOOK_FOR_DATA;
            encodeFlag = NOT_LOOKING_FOR_ENCODE;
            lcdFlagEncode = TRUE; //Display pre-fix on lcd

        
        //Check data by checking next 8 bits after the encoding
        }else if((dataFlag == LOOK_FOR_DATA) && (dataCount > DATA_LENGTH)){
            crabs = data;
            data = ZERO; //Restart data for decode
            dataCount = ZERO; 
            lcdFlagEncode = FALSE; //Turn off encode message
            lcdFlagData = TRUE; //Display data
            decodeFlag = LOOK_FOR_DECODE;
            dataFlag = NOT_LOOKING_FOR_DATA;
        
        //Check decoding by checking the next 16 bits after the data
        }else if((decodeFlag == LOOK_FOR_DECODE) && (dataCount > DECODE_LENGTH)){
            if(data == TX_DECODING){
             lcdFlagDecode = TRUE;
            }else{
                decodeWrong = TRUE;
            }
            decodeFlag = NOT_LOOKING_FOR_DECODE;
            encodeFlag = LOOK_FOR_ENCODE;
        }
        
        levelCounter = ZERO;
    }
} //end CY_ISR(LevelCount)