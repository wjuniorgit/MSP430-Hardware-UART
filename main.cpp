#include "msp430g2553.h"
#include "hardUart.h"



int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	         // Stop watchdog timer

	if (CALDCO_16MHZ == 0xFF)		     // If calibration constant erased
			{
		while (1)
			;                            // do not load, trap CPU!!
	}

	DCOCTL = 0;                          // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_16MHZ;              // Set DCO
	DCOCTL = CALBC1_16MHZ;


	hardUart hu;

	_BIS_SR(GIE);     // Enable CPU interrupts


	hu.xmit("\n\rHardware UART\n\r");


	}



