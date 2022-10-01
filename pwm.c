//  The program to implement the PWM module to generate a 40kHz signal with a duty cycle of 50% on pin OC1 of the PIC32MX460F512L
// microcontroller.Timer 2 is used for the timing of the PWM signal.
void Configure_PWM_Module(void)
{
	T2CONbits.T32 = 0;               // Timer 2 in 16 bit mode
	OC1CONbits.OC32 = 0;         // 16 bit operation
	PR2 = 1999;                           // Load PR2
	OC1RS = 1000;                     // Load duty cycle
	OC1CONbits.OCM = 6;         // Enable PWM module
	OC1CONbits.OCTSEL = 0;   // TIMER 2 is the source
	T2CONbits.TCKPS = 0;        // Set Timer 2 prescaler = 1
	T2CONbits.ON = 1;               // Enable Timer 2
	OC1CONbits.ON = 1;             // Enable OC1CON
}
//start main program
void main(void)
{
	TRISDO_bit=0;                          //Configure OC1 as output
	configure_PWM_Module();      //Configure the PWM module
	for(;;)                                          // Wait here,PWM module does all the work
{
}
}
  
