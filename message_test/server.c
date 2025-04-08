#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include "message.h"
#include <errno.h>

int main(void) {
	int chid;
	rcvid_t rcvid;
	mymsg_t msg;
	mymsg_t reply_msg;
	reply_msg.a = 12;
	reply_msg.b = 19;

	puts("Running Server!!!"); /* prints Hello World!!! */
	//send channel number

	//step1 create the channel with 0 as default flag
	chid = ChannelCreate(0);

	while(1)
	{
		//receive from client
		//step2 . go to receive blocked state and wait (blocked)
		rcvid = MsgReceive(chid,&msg,sizeof(msg),NULL);
		puts("Received message!!!"); /* prints Hello World!!! */
		//do some process
		//we are here means we got something from a client
		printf("a= %d , b= %d\n",msg.a,msg.b);
		//reply back with another message
		//step 3 replay back on the same id that we received message from
		MsgReply(rcvid,EOK,&reply_msg,sizeof(reply_msg));
		puts("Reply Sent!!!"); /* prints Hello World!!! */
	}
	return EXIT_SUCCESS;
}
