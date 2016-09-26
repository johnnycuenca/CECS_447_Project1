// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Johnny Cuenca, Christian Bracamontes
// September 19, 2016

/*  Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "PLL.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "EdgeTrigured_Init.h"
#include "Nokia5110.h"

void display(void);
void Delay(unsigned long);

char string[20];  // global to assist in debugging


//debug code
int main(void){
  unsigned char i;				//Used to receive an input from terminal
	EdgeTrigured_Init();			//initialize edge counter interupt on PF4, PF0
	PortF_Init();						//initialized port F, PF4 and PF0 inputs, PF1,PF2,PF3 as outputs LEDS

  Nokia5110_Init();	 //Nokia Initialization
	PLL_Init();							//initialze PLL at 50Mhz clock
  UART_Init();            //initialize UART on Port A with baud rate of 115,200
  OutCRLF();
	UART_OutString("CECS 447");
  OutCRLF();
	UART_OutString("Project 1: Part 1");
  OutCRLF();
	UART_OutString("Johnny Cuenca, Christian Bracamontes");
  OutCRLF();
  
  while(1){
		//ofb7f7fbfi
		i = UART_InChar();
		if(i == 'g' || i == 'G'){																	//check if g or G input
			GPIO_PORTF_DATA_R &= 0x08;															//used to clear data port, turn off other leds
			GPIO_PORTF_DATA_R ^= 0x08;															//turn on green LED, and toggle it.
			if((GPIO_PORTF_DATA_R &= 0x08) == 0){										//check if Green LED is off
				UART_OutString("Green LED is off");OutCRLF();}				//Display green LED off.
			else{
				UART_OutString("Green LED is on");OutCRLF();}					//Display Green LED on.
		}
		else if(i == 'r' || i == 'R'){														//check if r or R input
			GPIO_PORTF_DATA_R &= 0x02;															//used to clear data port, turn off other leds 
			GPIO_PORTF_DATA_R ^= 0x02;															//turn on Red LED, and toggle it.
			if((GPIO_PORTF_DATA_R &= 0x02) == 0){										//check if Red LED is off
				UART_OutString("Red LED is off");OutCRLF();}					//Display RED LED off.
			else{
				UART_OutString("Red LED is on");OutCRLF();}						//Display RED LED on.
		}
		else if(i == 'b' || i == 'B'){														//check if b or B input
			GPIO_PORTF_DATA_R &= 0x04;															//used to clear data port, turn off other leds 
			GPIO_PORTF_DATA_R ^= 0x04;															//turn on Blue LED, and toggle it.
			if((GPIO_PORTF_DATA_R &= 0x04) == 0){										//check if Blue LED is off
				UART_OutString("Blue LED is off");OutCRLF();}					//Display RED Blue off.
			else{
				UART_OutString("Blue LED is on");OutCRLF();}					//Display RED Blue on.
		}
		else{
			UART_OutString("InString: ");
			UART_InString(string,19);
			UART_OutString(" OutString="); UART_OutString(string); OutCRLF();
		}
		display();
		Delay(833333);
  }
}

void display(void){
		Nokia5110_Clear(); 
		Nokia5110_SetCursor(0,2);
		Nokia5110_OutString(string);// Used to display a seperator between the two 
//		Nokia5110_SetCursor(0,3);						//sencors.
//		Nokia5110_OutString("     || ");
//		Nokia5110_SetCursor(0,4);
//		Nokia5110_OutString("     || ");
//		Nokia5110_SetCursor(0,5);
//		Nokia5110_OutString("     || ");
//		Nokia5110_SetCursor(5,0);          
}

void Delay(unsigned long ulCount){// Used to produce a 50hz delay in the main.
  do{
    ulCount--;
	}while(ulCount);
}
