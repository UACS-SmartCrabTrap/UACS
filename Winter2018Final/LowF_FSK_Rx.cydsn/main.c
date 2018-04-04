/*included files*/
#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

/*definitions*/
#define TX_ENCODING 0xFFFF
#define TX_DECODING 0x0001

#define ONE_THRESHOLD 7
#define LEVEL_COUNTER_CHECK_BIT_TIME 10
#define DATA_LENGTH 7
#define DECODE_LENGTH 15

/*function prototypes*/
CY_ISR_PROTO(LevelCount);

/*global variables*/
static uint16 levelCounter = 0;
static uint8 zeroCount = 0; 
static uint8 oneCount = 0; 
//static uint8 messageBit = 0; 
static uint8 currentBit = 0;
static uint8 dataCount = 0;
static uint8 data = 0;
static uint8 crabs = 0;
static uint8 dataFlag = 0;
static uint8 decodeFlag = 0;
static uint8 decodeWrong = 0;

//FLAGS
static uint8 lcdFlagEncode = 0;
static uint8 lcdFlagData = 0;
static uint8 lcdFlagDecode = 0;

/*
 * function: main()
 * parameters: none
 * returns: should never return
 * description:
 */
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    BPF_Comp_Start();
    ShiftReg_Start();
    Ref_OpAmp_Start();
    PGA_Start() ; 
    OutComp_Start();
    LevelCount_Start();
    LevelCountISR_StartEx(LevelCount);
    
    HighF_BPF_Comp_Start();
    HighF_ShiftReg_Start();
    HighF_Ref_OpAmp_Start();
    HighF_PGA_Start() ; 
    HighF_OutComp_Start();
    HighF_LevelCount_Start();
    LCD_Char_Start();
    //LeveCountISR_StartEx(LevelCheck);
    
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
            decodeWrong = 0;
        }
    } //end for(;;)
} //end main()
    

//Bit length = 0.5s
//timer period = 0.05s
//will check bit 10 times, to debounce
//will set bit after 0.4s (8 checks) 
CY_ISR(LevelCount){
    levelCounter++;
    
    if(OutComp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    //debouncing every 0.4s, with a check of 7/8 hits 
    if(levelCounter == LEVEL_COUNTER_CHECK_BIT_TIME){
        if(oneCount >= ONE_THRESHOLD){
            currentBit = 0x01;
            oneCount = 0;
        }else{
            currentBit = 0x00; 
            zeroCount = 0; 
        }
        dataCount++;
        levelCounter = 0;
        //CountOut_Write(currentBit);
        
        //Look for pre-fix
        data = data << 1;
        data = data | currentBit;
        if((data == TX_ENCODING) && (dataFlag == 0) && (decodeFlag == 0)){
            CountOut_Write(1);
            dataCount = 0;
            data = 0x00;
            dataFlag = 1; //Start looking for data
            lcdFlagEncode = 1; //Display pre-fix on lcd

        
        // Look for data
        }else if((dataFlag == 1) && (dataCount > DATA_LENGTH)){
            crabs = data;
            data = 0; //Restart data for decode
            dataCount = 0; 
            lcdFlagEncode = 0; //Turn off encode message
            lcdFlagData = 1; //Display data
            decodeFlag = 1; //Now go to decode stage
        }
        
        if(decodeFlag == 1 && (dataCount > DECODE_LENGTH)){
            if(data == TX_DECODING){
             lcdFlagDecode = 1;
            }else{
                decodeWrong = 1;
            }
            decodeFlag = 0;
            dataFlag = 0; //Don't want to check for data anymore
        }
    }
} //end CY_ISR(LevelCount)