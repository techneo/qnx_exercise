/*
 * message.h
 *
 *  Created on: 01-Apr-2025
 *      Author: suren
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

struct payload
{
	int a;
	int b;
};

typedef union
{
	struct _pulse pulse;
	struct payload mypayload;
	//int a;
	//int b;
}mymsg_t;


#define PULSE_1  1
#define PULSE_2  2


#endif /* MESSAGE_H_ */
