#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include "message.h"
#include <errno.h>
#include <unistd.h>

int main(void) {
	int chid;
	rcvid_t rcvid;
	mymsg_t msg;
	mymsg_t reply_msg;
	int pid;
	reply_msg.mypayload.a = 12;
	reply_msg.mypayload.b = 19;

	puts("Running Server!!!"); /* prints Hello World!!! */
	//send channel number

	//step1 create the channel with 0 as default flag
	chid = ChannelCreate(0);

	pid = getpid(); //get our own pid
	printf("Server's pid: %d, chid: %d\n", pid, chid); //print our pid/chid so

	while(1)
	{
		//receive from client
		//step2 . go to receive blocked state and wait (blocked)
		rcvid = MsgReceive(chid,&msg,sizeof(msg),NULL);
		if (rcvid==0)
		{
			puts("Pulse message!!!\n");
			//our msg has the pulse as union. value is again a union
			printf("pulse data %d,%d\n",msg.pulse.code,msg.pulse.value.sival_int);

			switch(msg.pulse.code)
			{
			case PULSE_1:
				puts("Pulse 1!!!\n");
				break;
			case PULSE_2:
				puts("Pulse 2!!!\n");
				break;
			default:
				puts("Invalid Pulse !!!\n");
				break;
			}
		}
		else
		{
			puts("Received message!!!"); /* prints Hello World!!! */
			//do some process
			//we are here means we got something from a client
			printf("a= %d , b= %d\n",msg.mypayload.a,msg.mypayload.b);
			//reply back with another message
			//step 3 replay back on the same id that we received message from
			MsgReply(rcvid,EOK,&reply_msg,sizeof(reply_msg));
			puts("Reply Sent!!!"); /* prints Hello World!!! */
		}
	}
	return EXIT_SUCCESS;
}
