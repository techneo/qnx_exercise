#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include "message.h"
#include <errno.h>


int main(void) {

	int coid;
	mymsg_t out;
	mymsg_t incoming_msg;
	puts("Starting Client!!!");

	int server_pid,server_chid;

	//step1 get the pid and chid from pidin
	server_pid = 74551298; //need to find the PID using pidin
	server_chid = 1;

	//step2 set the message value
	out.a = 1;
	out.b = 2;

	//step3 Attach to the channel as side channel and get coid
	// if side channel is not used , kernel may open a file descriptor
	coid = ConnectAttach(0,server_pid,server_chid,_NTO_SIDE_CHANNEL,0);
	if (coid == -1)
	{
		//either server is not running or the pid is wrong.
		puts("Attach failed, Invalid pid or chid");
		return EXIT_FAILURE;
	}
	// we are here means the pid and chid are valid
	puts("Connected to Server , Sending Payload\n");
	//step4 send the message request to the server on the coid received
	MsgSend(coid,&out,sizeof(out),&incoming_msg,sizeof(incoming_msg));
	puts("Receiving Reply\n");
	printf("a= %d , b= %d\n",incoming_msg.a,incoming_msg.b);
	return EXIT_SUCCESS;
}
