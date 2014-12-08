//-----------------------------------------------------------------
// Name:	Chris Kiernan
// File:	Lab 7
// Date:	Started 3 Dec 14
// Purp:	Collect samples from P1.3-P1.5 in order
//-----------------------------------------------------------------
#include "msp430g2553.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short CTRsample[16];								// Just to analyze the values
	unsigned short RGTsample[16];
	unsigned short LFTsample[16];
	unsigned char i = 0;										// index into sample array
	unsigned char j = 0;
	unsigned char k = 0;

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR |= BIT0;												// Set the red LED as output
	P1DIR |= BIT6;

	while(1) {

		// LEFT SENSOR READ
		ADC10CTL0 = 0;
		ADC10CTL1 = INCH_3 | ADC10DIV_3;
		ADC10AE0 = BIT3;
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;
		while(ADC10CTL1 & ADC10BUSY);
		LFTsample[i] = ADC10MEM;
		if (LFTsample[i] > 0x02B0){
			P1OUT |= BIT0;
		}


		// CENTER SENSOR READ
		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;		 								// Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		CTRsample[j] = ADC10MEM;									// collect that 10-bit value
		if (CTRsample[j] > 0x02B0){
			P1OUT |= BIT0;
			P1OUT |= BIT6;
		}

		// RIGHT SENSOR READ
		ADC10CTL0 = 0;
		ADC10CTL1 = INCH_5 | ADC10DIV_3;
		ADC10AE0 = BIT5;
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;
		while(ADC10CTL1 & ADC10BUSY);
		RGTsample[k] = ADC10MEM;
		if (RGTsample[k] > 0x02B0){
			P1OUT |= BIT6;
		}

		if (LFTsample[i]<0x02B0 && CTRsample[j]<0x02B0 && RGTsample[k]<0x02B0){
			P1OUT &= ~BIT0;
			P1OUT &= ~BIT6;
		}
		i = (i+1) & 0xF;										// This is a mod 16 increment
		i=0;
		j=0;
		k=0;
	} // end infinite loop

} // end main

