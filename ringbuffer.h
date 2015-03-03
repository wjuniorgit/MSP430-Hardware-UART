/*
 * ringbuffer.h
 *
 *  Created on: 09/06/2014
 *      Author: Wellington
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_


template<typename T, int BUFFERSIZE>
class ringbuffer {
public:
	ringbuffer();
	virtual ~ringbuffer();
	bool empty();
	void push_back(T);
	T pop_front();
	void clear_buffer();
private:
	int head;
	int tail;
	T buffer[BUFFERSIZE];



};

template<typename T, int BUFFERSIZE>
ringbuffer<T,BUFFERSIZE>::ringbuffer() {

	clear_buffer();
}

template<typename T, int BUFFERSIZE>
ringbuffer<T,BUFFERSIZE>::~ringbuffer() {
}

template<typename T, int BUFFERSIZE>
bool ringbuffer<T,BUFFERSIZE>::empty() {
	return head == tail;
}
template<typename T, int BUFFERSIZE>
void ringbuffer<T,BUFFERSIZE>::clear_buffer(){
		 _disable_interrupts();


		head = 0;
		tail = 0;

		_enable_interrupts();
}


template<typename T, int BUFFERSIZE>
void ringbuffer<T,BUFFERSIZE>::push_back(T c){

	int i = (unsigned int)(head + 1);

	if(i == BUFFERSIZE){
		i=0;
	}
    if ( i != tail ) {
        buffer[head] = c;
        head = i;
    }
}


template<typename T, int BUFFERSIZE>
T ringbuffer<T,BUFFERSIZE>::pop_front() {
	    T c;

	    _disable_interrupts();

	    if (head != tail) {
	        c = buffer[tail];
	        tail = (unsigned int)(tail + 1);
	        if(tail==BUFFERSIZE){
	        	tail=0;
	        }

	    }
	    _enable_interrupts();
	    return c;
}



#endif /* RINGBUFFER_H_ */
