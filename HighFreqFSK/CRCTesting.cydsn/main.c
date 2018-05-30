/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "stdlib.h"

CY_ISR_PROTO(changeBitStream); // High F Interrupt

void CalculatCRC(void);

#define DATA 0b10011100
#define DATA_LENGTH 8
#define LINE_STR_LENGTH 12
#define BIT_0_MASK 0x01
#define BIT_1_MASK 0x02
#define BIT_2_MASK 0x04
#define BIT_3_MASK 0x08
#define BIT_4_MASK 0x10
#define BIT_5_MASK 0x20
#define BIT_6_MASK 0x40
#define BIT_7_MASK 0x80

#define DISP_DELAY          (1000u)     /* Display delay */
#define SEED_VALUE_COUNT    (20u)       /* Iteration amount */
#define in                     (1u)        /* Data input software value */

static int currentBit = 0;
static int bitValue = 0;
static int crc = 0;
char crcstring[LINE_STR_LENGTH];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* initialization/startup code */
    changeBitStream_StartEx(changeBitStream);
    LCD_Start();
    CRC_Init();
    Timer_1_Start();
    CRC_Start();
    
    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");
    
    for(;;)
    {
        switch(currentBit){
            case 0:
                bitValue = DATA & BIT_0_MASK;
                bitStream_Write(bitValue);
                break;
            case 1:
                bitValue = DATA & BIT_1_MASK;
                bitStream_Write(bitValue);
                break;
            case 2:
                bitValue = DATA & BIT_2_MASK;
                bitStream_Write(bitValue);
                break;
            case 3:
                bitValue = DATA & BIT_3_MASK;
                bitStream_Write(bitValue);                
                break;
            case 4:
                bitValue = DATA & BIT_4_MASK;
                bitStream_Write(bitValue);                
                break;
            case 5:
                bitValue = DATA & BIT_5_MASK;
                bitStream_Write(bitValue);
                break;
            case 6:
                bitValue = DATA & BIT_6_MASK;
                bitStream_Write(bitValue);
                break;
            case 7:
                bitValue = DATA & BIT_7_MASK;
                bitStream_Write(bitValue);
                
                break;
        }
//        if(currentBit > DATA_LENGTH-1){
//            CRC_Stop();
//            crc = CRC_ReadCRC();
//
//            /* Clear LCD line. */
//            LCD_Position(0u, 0u);
//            LCD_PrintString("                    ");
//
//            /* Output string on LCD. */
//            LCD_Position(0u, 0u);
//            sprintf(crcstring,"CRC : %d", crc);
//            LCD_PrintString(crcstring);
//        }
        CalculateCRC();
    }
}

void CalculateCRC(void)
{
    uint16 CRC_val = 0u;
    uint16 seed, poly, seed_msb, int_xor_1, int_xor_res, and_op, xor_op;
    uint8 i;
    poly = CRC_ReadPolynomial();
    seed = CRC_val; 
    seed_msb = CRC_val;
    for (i=0; i<SEED_VALUE_COUNT; i++)
    {
        seed_msb = seed_msb >> (CRC_CRC_SIZE - 1);
        seed_msb = seed_msb & 1u;
        int_xor_1 = seed_msb ^ in;

        if (int_xor_1 == 1u){
            int_xor_res = 0xffffu; 
        }else{
            int_xor_res = 0u; 
        }
        
        and_op = int_xor_res & poly;
        xor_op = seed ^ and_op;
        seed = xor_op << 1u;
        seed = seed | int_xor_1;
        seed_msb = seed;
        seed &= CRC_MASK;
    }
    /* Display Software calculated crc value on LCD */
    LCD_Position(0u,0u);
    LCD_PrintString("SV=");
    LCD_PrintInt16(seed);    
    CyDelay(DISP_DELAY);
}

/*******************************************************************************
* Function Name: changeBitStream

*******************************************************************************/
CY_ISR(changeBitStream)
{
    currentBit++;
    //LCD_PrintString("INTERRUPT");

}//end CY_ISR(changeBitStream)

/* [] END OF FILE */

