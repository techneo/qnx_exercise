/*
 *  intsimple.c
 *
 *  This module will contain code for handling an interrupt.
 *
 *  To test it, simply run it.  Note that you may have to do something
 *  to cause the interrupts to be generated (e.g. press a key if
 *  handling the keyboard interrupt).
 * 
 *  On an x86_64 box a good choice for the interrupt to use would be:
 *    1 - keyboard 
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/neutrino.h>

#define INT_KDB_PULSE (_PULSE_CODE_MINAVAIL+0)

#define KBD_INT 1

struct sigevent event;
struct _pulse msg;
int chid;
int self_coid;
int id;
rcvid_t rcvid;
int kb_isr;
int count;

#define EVENT_ISR 2

int main(int argc, char **argv)
{
	printf("starting...\n");

#if EVENT_ISR == 1
	//TODO set up an event if giving an event for the kernel to use to wake up
	// this thread.  Use whatever type of event and event handling you want
	chid = ChannelCreate(_NTO_CHF_PRIVATE);
	if (chid == -1)
	{
		perror("ChannelCreate()");
		exit(EXIT_FAILURE);
	}
	self_coid = ConnectAttach(0,0,chid,_NTO_SIDE_CHANNEL,0);
	if (self_coid == -1)
	{
		perror("ConnectAttach()");
		exit(EXIT_FAILURE);
	}
	SIGEV_PULSE_INIT(&event,self_coid,SIGEV_PULSE_PRIO_INHERIT,INT_KDB_PULSE,0);
	//give the kernel the event
	id = InterruptAttachEvent(KBD_INT, &event, 0);
	if(id == -1)
	{
		perror("InterruptAttachEvent()");
		exit(EXIT_FAILURE);
	}
#else
	//TODO either register as an IST
	id = InterruptAttachThread(KBD_INT,0);
	if(id == -1)
	{
		perror("InterruptAttachThread()");
		exit(EXIT_FAILURE);
	}
#endif




	while (1)
	{
		//TODO block here waiting for the interrupt
#if EVENT_ISR == 1
		//wait blocked for the pulse from kernel
		rcvid = MsgReceive(chid,&msg,sizeof(msg),NULL);
		//we got a pulse
		if (rcvid ==0)
		{
			if (msg.code == INT_KDB_PULSE)
			{
				printf("Even Pulse ISR hit\n");
			}
		}

#else
		if ( InterruptWait(_NTO_INTR_WAIT_FLAGS_FAST,NULL) == -1)
			{
				perror("InterruptWait()");
				exit(EXIT_FAILURE);
			}
		printf("IST Hit\n");
#endif
		if (InterruptUnmask(KBD_INT,id) == -1)
			{
				perror("InterruptUnmaks");
			}
		// if using a high frequency interrupt, don't print every interrupt
		printf("We got the event and unblocked, count=%d\n",count);
		count++;
	}
}
