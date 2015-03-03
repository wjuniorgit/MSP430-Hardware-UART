/*
 * hardUart.h
 *
 *  Created on: 29/05/2014
 *      Author: Wellington
 */


#ifndef HARDUART_H_
#define HARDUART_H_

#include "ringbuffer.h"

class hardUart{
public:
	hardUart();
	virtual ~hardUart();
	bool empty();
	int recv();
	void xmit(unsigned char);
	void xmit(const char *);
	unsigned char getCounter();

private:
	static ringbuffer<char,8> rb;
	static __interrupt void USCI0RX_ISR(void);

};



#endif /* HARDUART_H_ */
