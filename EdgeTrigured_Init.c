#include "tm4c123gh6pm.h"
#include "EdgeTrigured_Init.h"
#include "UART.h"

// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED
// Inputs: None
// Outputs: None
// Notes: These five pins are connected to hardware on the LaunchPad
void EdgeTrigured_Init(void){                          
  SYSCTL_RCGC2_R |= 0x00000020; // (a) activate clock for port F
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4 and PF0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x11;  //     disable alt funct on PF4 and PF0
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4 and PF0  
  GPIO_PORTF_PCTL_R &= ~0x000F000F; // configure PF4 and PF0 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x11;       //     disable analog functionality on PF
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4 and PF0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4 and PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4 and PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4 and PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4 and PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; 
  NVIC_EN0_R = 0x50000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}
void GPIOPortF_Handler(void){
	if(GPIO_PORTF_MIS_R &= 0x01){								//Check if switch 2 pressed
		GPIO_PORTF_DATA_R = 0;									//Turn on all LEDS
    UART_OutString("ALL LEDS turned off");			//Out put "ALL LEDS turned on" on terminal
		OutCRLF();
		GPIO_PORTF_ICR_R = 0x01;									//clear flag
	}
	else if(GPIO_PORTF_MIS_R &= 0x10){					//check if switch 1 pressed
		GPIO_PORTF_DATA_R = 0x0E;										//Turn off all LEDS
		UART_OutString("ALL LEDS turned on");		//output "ALL LEDS turned off" on terminal
		OutCRLF();
		GPIO_PORTF_ICR_R = 0x10;									//clear flag
	}
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
