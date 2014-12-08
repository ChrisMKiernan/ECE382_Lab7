//-----------------------------------------------------------------
// Name:	Chris Kiernan
// File:	Lab 7
// Date:	Started 3 Dec 14
// Purp:	Collect samples from P1.3-P1.5 in order
// Note:	I use polling in this system to read the values from all
//			of the sensors, which is less efficient. However, for the
//			speed of our clock, the difference is not significant
//-----------------------------------------------------------------
#include "msp430g2553.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short CTRsample[16];								// Arrays to hold the values of the ADC conversions
	unsigned short RGTsample[16];
	unsigned short LFTsample[16];
	unsigned char i = 0;										// indexes into sample arrays
	unsigned char j = 0;
	unsigned char k = 0;

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR |= BIT0;												// Set the red LED as output
	P1DIR |= BIT6;												// Set the green LED as output

	while(1) {

		// LEFT SENSOR READ
		//--------------------
		ADC10CTL0 = 0;											// Turn off ADC to make changes
		ADC10CTL1 = INCH_3 | ADC10DIV_3;						// Use channel A3, CLK/4
		ADC10AE0 = BIT3;										// Enable P1.3 as input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// ADC Conversion
		while(ADC10CTL1 & ADC10BUSY);
		LFTsample[i] = ADC10MEM;								// Collect value from ADC
		if (LFTsample[i] > 0x02B0){								// Compare to threshold value to turn on LED
			P1OUT |= BIT0;
		}


		// CENTER SENSOR READ
		//----------------------
		ADC10CTL0 = 0;											// Turn off ADC to make changes
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Use channel A4, CLK/4
		ADC10AE0 = BIT4;		 								// Enable P1.4 as input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// ADC Conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		CTRsample[j] = ADC10MEM;								// Collect value from ADC
		if (CTRsample[j] > 0x02B0){								// Compare to threshold value to turn on LED
			P1OUT |= BIT0;
			P1OUT |= BIT6;
		}

		// RIGHT SENSOR READ
		//---------------------
		ADC10CTL0 = 0;											// Turn off ADC to make changes
		ADC10CTL1 = INCH_5 | ADC10DIV_3;						// Use channel A5, CLK/4
		ADC10AE0 = BIT5;										// Enable P1.5 as ADC input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// ADC conversion
		while(ADC10CTL1 & ADC10BUSY);
		RGTsample[k] = ADC10MEM;
		if (RGTsample[k] > 0x02B0){								// Compare ADC value to threshold to turn on LED
			P1OUT |= BIT6;
		}

																// Below turns off the LEDs if there is no sensor reading
		if (LFTsample[i]<0x02B0 && CTRsample[j]<0x02B0 && RGTsample[k]<0x02B0){
			P1OUT &= ~BIT0;
			P1OUT &= ~BIT6;
		}

		i = (i+1) & 0xF;										// This is a mod 16 increment
		i=0;													// Reset the array values
		j=0;
		k=0;
	} // end infinite loop

} // end main

