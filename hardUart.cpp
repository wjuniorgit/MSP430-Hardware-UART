/*
 * hardUart.c
 *
 *  Created on: 29/05/2014
 *      Author: Wellington
 */
#include "msp430g2553.h"
#include "hardUart.h"
#include "globals.h"

//ringbuffer<char,16> hardUart::rb;
ringbuffer<char,8> hardUart::rb;

hardUart::hardUart() {

	P1SEL = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;                    // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2; // use SMCLK for USCI clock
	UCA0BR0 = 130; // 16MHz 9600
	UCA0BR1 = 6; // 16MHz 9600
	UCA0MCTL = UCBRS1 + UCBRS0; // Modulation UCBRSx = 3

	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

}

//template<typename T_STORAGE>
hardUart::~hardUart() {
}

//template<typename T_STORAGE>
bool hardUart::empty() {
	return rb.empty();
}

//template<typename T_STORAGE>
int hardUart::recv() {
	return rb.pop_front();
}

//template<typename T_STORAGE>
void hardUart::xmit(unsigned char c) {
	while (!(IFG2 & UCA0TXIFG))
		; // USCI_A0 TX buffer ready?

	UCA0TXBUF = (unsigned char) c; // TX -> RXed character
}

//template<typename T_STORAGE>
void hardUart::xmit(const char *s) {
	while (*s) {
		xmit((unsigned char) *s);
		++s;
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void hardUart::USCI0RX_ISR(void) {
	rb.push_back(UCA0RXBUF);
}

