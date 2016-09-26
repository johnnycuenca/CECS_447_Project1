

void EnableInterrupts(void);		

// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED
// Inputs: None
// Outputs: None
// Notes: These five pins are connected to hardware on the LaunchPad
void EdgeTrigured_Init(void);

//Initialilze port F with PF4 and PF1 as inputs (On board push buttons)
//and with PF1, PF2, PF3 as outputs (on board LEDS)
void PortF_Init(void);
