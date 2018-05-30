/* =============================================================================
 * Smart Crab Trap
 * High FSK Rx
 * Edited by: Stephanie Salazar
 * Revision: 5/29/18
 * Function: This project takes in a signal from an outside source
 * and reads the data within the signal. This code waits for a pre-fix
 * of 0xFF and then reads the next 4 bits as the data and confirms
 * the message with a post-fix of 0x01. The data is displayed on an LCD display.
 * =============================================================================
*/

#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

#define ARRAY_SIZE        12
#define COUNT             100
#define PREFIX_ACCURACY   90
#define DATA_ACCURACY     70
#define DATA_LENGTH       7
#define PREFIX            0xFF
#define POSTFIX           0x01
#define SUCCESS           0x1
#define FAILURE           0x0
#define TRUE              0x1
#define FALSE             0x0
#define ON                0x1
#define OFF               0x0
#define FiveSecs          5000
#define TRANSMISSIONS_3   2
#define Delay             2
#define DATA_STORED       3

#define BIT_0_MASK 0x01
#define BIT_1_MASK 0x02
#define BIT_2_MASK 0x04
#define BIT_3_MASK 0x08
#define BIT_4_MASK 0x10
#define BIT_5_MASK 0x20
#define BIT_6_MASK 0x40
#define BIT_7_MASK 0x80

/*Function Prototypes*/
void Display(void);
int CheckParity(int);
void SendData(void);
void startModules(void);
void stopModules(void);

// Interrupt for switching bits 5 ms
CY_ISR_PROTO(Bit_Timer);
CY_ISR_PROTO(watchDogCheck);
CY_ISR_PROTO(wakeUp_ISR);

// Global Variables
static uint16 levelCounter = 0; // Timer counter to debounce bit
static uint16 zeroCount = 0; // 0 count used in timer counter debounce
static uint16 oneCount = 0; // 1 count used in timer counter debounce
static uint8 currentBit = 0; // x/10 bit decision for 500 ms bit
static uint8 dataCount = 0; // which bit of data we are looking at
static uint16 data = 0; // byte bits of data
static uint16 crabs = 0; // byte of data transferred from data variable
static uint8 dataFlag = 0; // Flag to start looking for data
static uint8 decodeFlag = 0; // Flag to start looking for post-fix
static uint8 paritySuccess = 0; // Flag for whether transmitted parity matches data
static uint8 threeTransmissions = 0; // checks for 3 transmission before reinstatiating sleep timer
static uint8 sleepFlag = FALSE; 

// LCD String Variables
static char OutputString[ARRAY_SIZE];
static char display[ARRAY_SIZE];

// Store Received Data
static uint8 allData[DATA_STORED];
static uint8 parityResult[DATA_STORED];
static uint8 postFixResult[DATA_STORED];

// FLAGS for turning on messages on LCD screen
static uint8 lcdFlagEncode = FALSE; // Turns on pre-fix message
static uint8 lcdFlagData = FALSE; // Displays data 
static uint8 lcdFlagDecode = FALSE; // good or bad postfix
static uint8 decodeWrong = FALSE;


int main(void)
{
    CyGlobalIntEnable; 
    
    /* Module is turned on- will display again if watchdog timer is enabled */
    LCD_Char_Start();
    sprintf(display, "Starting Module!");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);
    CyDelay(500);

    /* initialization/startup code here */
    Timer_ISR_StartEx(Bit_Timer);
    Sleep_ISR_StartEx(wakeUp_ISR);
    watchDogCheck_StartEx(watchDogCheck); 
      
    // Start watch dog timer to check for blocks in code
    CyWdtStart(CYWDT_16_TICKS, CYWDT_LPMODE_NOCHANGE); // 4-6 ms
    
    SleepTimer_Start();

    // Displays Loading Message before receiving pre-fix=
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);
    
    Power_Toggle_Write(ON); // Turn analog circuit on

    for(;;)
    {
        Display();
        // PSoC Sleep command. To adjust sleep time, change in the hardware
        //  block. No sleep time parameters taken in PSoC5LP.
        //  PM_SLEEP_TIME_NONE is a relic of PSoC3
        if(sleepFlag == TRUE){
            sleepFlag = FALSE; 
            Power_Toggle_Write(FALSE);
            stopModules(); 
            CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);
        }
    } // end of for(;;)
    
} // end of main()


///*********************************************************************
// * ISR: Bit_Timer
// * parameters: void
// * returns: void
// * description: Bit length is 500 ms. Bit_Timer checks every 5 ms for
// * a one or zero. After 100 checks, it decides the bit and looks for
// * the prefix 0xff. If seen, record data. 
// *********************************************************************
// */
CY_ISR(Bit_Timer){
    levelCounter++;
    
    // Count whether bit is currently 1 or 0
    if(Out_Comp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    // Debouncing
    if(levelCounter == COUNT){
        if((dataFlag == FALSE) && (decodeFlag == FALSE)){ //looking for prefix
            if(oneCount >= PREFIX_ACCURACY){ // 1 bit must be Accuracy/100 = 1 
                currentBit = 0x01;
                oneCount = 0;
                Count_Out_Write(1);
        
            }else{ // if oneCount <= PREFIX_ACCURACY, bit is 0
                currentBit = 0x00; 
                zeroCount = 0; 
                Count_Out_Write(0);
            
            }
        }else{ // looking for data bits, can have less accuracy
            if(oneCount >= DATA_ACCURACY){ // 1 bit must be Accuracy/100 = 1 
                currentBit = 0x01;
                oneCount = 0;
                Count_Out_Write(1);
        
            }else{ // if oneCount <= DATA_ACCURACY, bit is 0
                currentBit = 0x00; 
                zeroCount = 0; 
                Count_Out_Write(0);
            
            }
        }
        dataCount++; // Keep track of what bit we are on
        levelCounter = 0; // Reset timer bit debouncer  
        
        //Look for pre-fix
        data = data << 1; // Shift data over to store next bit
        data = data | currentBit;
        // Check if data is prefix(oxFF) but we are not looking for data or decode
        if(((data & PREFIX) == PREFIX) && (dataFlag == FALSE) && (decodeFlag == FALSE)){ 
            dataCount = 0;
            data = 0;
            dataFlag = TRUE; //Start looking for data
            lcdFlagEncode = TRUE; //Display pre-fix on lcd
        
        //Check data by checking next 8 bits and parity (9 bits) after the encoding
        }else if((dataFlag == TRUE) && (dataCount > DATA_LENGTH+1)){
            crabs = data;
            data = 0; //Restart data for decode
            dataCount = 0; 
            lcdFlagEncode = FALSE; //Turn off encode message
            lcdFlagData = TRUE; //Display data
            decodeFlag = TRUE;
        }
        
        // Check for 8 bits of post-fix
        if(decodeFlag == TRUE && (dataCount > DATA_LENGTH)){
            // Correct postfix is 0x01
            if(data == POSTFIX){
             lcdFlagDecode = TRUE; // lcd flag for "good" post-fix
            }else{
                decodeWrong = TRUE; // lcd flag for "bad" post-fix
            }
            decodeFlag = FALSE;
            dataFlag = FALSE; //Don't want to check for data anymore
        }
        
    } // end of if(levelCounter == COUNT)
} /* END OF CY_ISR(HighF_LevelCount) */

///*********************************************************************
// * ISR: watchDogCheck
// * parameters: void
// * returns: void
// * description: Clears watchdog timer to avoid reset unless timing 
// * has drifted
// *********************************************************************
// */
CY_ISR(watchDogCheck){
    
    CyWdtClear(); 
        
} /* END OF CY_ISR(watchDogCheck) */

///*********************************************************************
// * ISR: wakeUp_ISR
// * parameters: void
// * returns: void
// * description: Checks for prefix and disables sleep if prefix is seen
// * Timer is enabled to restart sleep if false positive
// * If no prefix, disable interrupt and nothing else
// *********************************************************************
// */
CY_ISR(wakeUp_ISR){
    
    CyWdtClear(); 
    SleepTimer_GetStatus(); // Clears the sleep timer interrupt
    Power_Toggle_Write(TRUE);
    startModules();
//    sleepToggle_Write(TRUE);
//    CyDelay(Delay);
//    sleepToggle_Write(FALSE);
    
    // If output is high
    if(Out_Comp_GetCompare() != 0){
        SleepTimer_Stop();
        Bit_Timer_Start();
        //trigger interrupt to avoid data loss 
        Timer_ISR_Enable();
        Timer_ISR_SetPending();
    }else{
        sleepFlag = TRUE; 
    }

}/* END OF wakeUp_ISR */


///*********************************************************************
// * function: void Display(void)
// * parameters: void
// * returns: void
// * description: Displays current data on LCD display depending
// * on what flags are set
// *********************************************************************
// */
void Display()
{
    // LCD Screen Messages
    // If encode is received, display message
    if(lcdFlagEncode == TRUE){
        LCD_Char_ClearDisplay();
        LCD_Char_PrintString("0xFF pre-fix");
        lcdFlagEncode = FALSE; 
    // When 9 bits are received, data will display at top of screen
    }else if(lcdFlagData == TRUE){
        paritySuccess = CheckParity(crabs);
        crabs = crabs >> 1;
        sprintf(OutputString, "Crabs:%i Err:%i",crabs, !paritySuccess);
        LCD_Char_ClearDisplay();
        LCD_Char_Position(0u,0u);
        LCD_Char_PrintString(OutputString);
        dataFlag = FALSE;
        lcdFlagData = FALSE;
    // Postfix will display good or bad below data on screen
    }else if(lcdFlagDecode == TRUE){
        LCD_Char_Position(1u,0u);
        char8 displayG[] = "good";
        LCD_Char_PrintString(displayG);
        dataFlag = FALSE;
        lcdFlagDecode = FALSE;
    }else if(decodeWrong == TRUE){
        LCD_Char_Position(1u,0u);
        char8 displayB[] = "bad";
        LCD_Char_PrintString(displayB);
        decodeWrong = FALSE;
    }
} /* END OF Display() */

///********************************************************************
// * function: void CheckParity(void)
// * parameters: int received data including parity
// * returns: int whether 
// * description: XORs each bit of data to get even or odd parity for
// * error checking
// ********************************************************************
// */
int CheckParity(crabs)
{
    int i = 0;
    int bitToCheck = crabs >> 1; // Remove parity from data
    int receivedParity = (crabs & BIT_0_MASK); //Save parity from data received
    int parity = bitToCheck & BIT_0_MASK; // Get first bit of data to XOR
    for(i = 0; i < DATA_LENGTH; i++){
        bitToCheck = bitToCheck >> 1; // shift mask over
        parity = (bitToCheck & BIT_0_MASK) ^ parity; // XOR new bit
    }
    if(parity == receivedParity){
        return SUCCESS;
    }else{
        return FAILURE;
    }
} /* END OF CheckParity() */

///*******************************************************************
// * function: void SendData(void)
// * parameters: void
// * returns: void
// * description: Sends received data through UART 
// * Order sent is: 1 byte: Data
// *                1 bit : Success/Failure
// *******************************************************************
//*/
void SendData()
{
    UART_WriteTxData(crabs);
    if((paritySuccess == SUCCESS) && (decodeWrong != TRUE)){
        UART_WriteTxData(SUCCESS);
    }else{
        UART_WriteTxData(FAILURE);
    }
} /* END OF SendData() */

void stopModules(void){
    LCD_Char_Sleep();
    UART_Sleep();
    PWM_Recon_Sleep();
    Shift_Reg_Sleep();
    Out_Comp_Sleep();
    Bit_Timer_Sleep();
    checkWatchDogTimer_Sleep();
    CyPmSaveClocks();

}

void startModules(void){
    CyPmRestoreClocks();
    LCD_Char_Wakeup();
    UART_Wakeup();
    PWM_Recon_Wakeup();
    Shift_Reg_Wakeup();
    Out_Comp_Wakeup();
    // Start timer to clear watch dog
    checkWatchDogTimer_Wakeup();
    checkWatchDogTimer_Start();
}

uint8 majorityVote(){
    int i = 0;
    int success = 0;
    uint8 finalResult = 0;
    for(i = 0; i<DATA_STORED; i++){
        if((parityResult[i] == SUCCESS) && (postFixResult[i] == SUCCESS)){
            success++;
        }
        if(success >= DATA_STORED){
            finalResult = allData[0];
        }else{
            int zero1 = allData[0] & BIT_0_MASK;
            int zero2 = allData[1] & BIT_0_MASK;
            int zero3 = allData[2] & BIT_0_MASK;
            int zeros = zero1 + zero2 + zero3;
            if(zeros > 1){
                finalResult = finalResult | BIT_0_MASK;
            }
            int one1 = allData[0] & BIT_1_MASK;
            int one2 = allData[1] & BIT_1_MASK;
            int one3 = allData[2] & BIT_1_MASK;
            int ones = one1 + one2 + one3;
            if(ones > 1){
                finalResult = finalResult | BIT_1_MASK;
            }
            int two1 = allData[0] & BIT_2_MASK;
            int two2 = allData[1] & BIT_2_MASK;
            int two3 = allData[2] & BIT_2_MASK;
            int twos = two1 + two2 + two3;
            if(twos > 1){
                finalResult = finalResult | BIT_2_MASK;
            }
            int three1 = allData[0] & BIT_3_MASK;
            int three2 = allData[1] & BIT_3_MASK;
            int three3 = allData[2] & BIT_3_MASK;
            int threes = three1 + three2 + three3;
            if(threes > 1){
                finalResult = finalResult | BIT_3_MASK;
            }
            int four1 = allData[0] & BIT_4_MASK;
            int four2 = allData[1] & BIT_4_MASK;
            int four3 = allData[2] & BIT_4_MASK;
            int fours = four1 + four2 + four3;
            if(fours > 1){
                finalResult = finalResult | BIT_4_MASK;
            }
            int five1 = allData[0] & BIT_5_MASK;
            int five2 = allData[1] & BIT_5_MASK;
            int five3 = allData[2] & BIT_5_MASK;
            int fives = five1 + five2 + five3;
            if(fives > 1){
                finalResult = finalResult | BIT_5_MASK;
            }
            int six1 = allData[0] & BIT_6_MASK;
            int six2 = allData[1] & BIT_6_MASK;
            int six3 = allData[2] & BIT_6_MASK;
            int sixes = six1 + six2 + six3;
            if(sixes > 1){
                finalResult = finalResult | BIT_6_MASK;
            }
            int seven1 = allData[0] & BIT_7_MASK;
            int seven2 = allData[1] & BIT_7_MASK;
            int seven3 = allData[2] & BIT_7_MASK;
            int sevens = seven1 + seven2 + seven3;
            if(sevens > 1){
                finalResult = finalResult | BIT_7_MASK;
            }
        }
    }
    return finalResult;
}


/* [] END OF FILE */
