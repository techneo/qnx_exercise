////////////////////////////////////////////////////////////////////////////////
// server.c
//
// A QNX msg passing server.  It should receive a string from a client,
// calculate a checksum on it, and reply back the client with the checksum.
//
// The server prints out its pid and chid so that the client can be made aware
// of them.
//
// Using the comments below, put code in to complete the program.  Look up
// function arguments in the course book or the QNX documentation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <process.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/siginfo.h>

#include "msg_def.h"  //layout of msg's should be defined by a struct, here's its definition

int
calculate_checksum(char *text);

int main(void) {

	rcvid_t rcvid;
	rcvid_t save_rcvid;
	rx_msg_t msg;
	name_attach_t *attach;
	tx_msg_t tmsg;
	struct sigevent save_event;



	attach = name_attach(NULL,"myapp",0);

	if (attach==NULL)
	{
		puts("error attaching myapp");
		return EXIT_FAILURE;
	}



	while (1) {
		//PUT CODE HERE to receive msg from client

		rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

		if (rcvid == MSG_TYPE_INVALID) { //was there an error receiving msg?
			perror("MsgReceive"); //look up errno code and print
			exit(EXIT_FAILURE); //give up
		}
		printf("message rcvid %ld\n",rcvid);


		if(MsgVerifyEvent(rcvid,&msg.event)!=-1)
				{
					printf("MsgVerify in \n");
					save_event = msg.event;
					save_rcvid = rcvid;
					strcpy(tmsg.csum.string_to_cksum,"0xaa555");
					printf("MsgReply called \n");
					MsgReply(rcvid,0,&tmsg,sizeof(tmsg));

				}


		while(1)
		{
		printf("MsgDeliverEvent pre \n");
		sleep(10);
		MsgDeliverEvent(save_rcvid,&save_event);
		printf("MsgDeliverEvent post \n");
		}

	}

	return 0;
}

int calculate_checksum(char *text) {
	char *c;
	int cksum = 0;

	for (c = text; *c != '\0'; c++)
		cksum += *c;
	return cksum;
}

