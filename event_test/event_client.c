////////////////////////////////////////////////////////////////////////////////
// client.c
//
// A QNX msg passing client.  It's purpose is to send a string of text to a
// server.  The server calculates a checksum and replies back with it.  The client
// expects the reply to come back as an int
//
// This program program must be started with commandline args.  
// See  if(argc != 4) below
//
// To complete the exercise, put in the code, as explained in the comments below
// Look up function arguments in the course book or the QNX documentation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include "msg_def.h"

int main(int argc, char* argv[])
{
	int server_coid; //Connection ID to server
	int self_coid; //needed to get our own channel id
	int chid;
	int flags;
	rcvid_t rcvid;
	tx_msg_t msg;
	rx_msg_t rmsg;
	int incoming_checksum; //space for server's reply
	int status; //status return value used for MsgSend
	//int server_pid; //server's process ID
	//int server_chid; //server's channel ID

//	if (argc != 2)
//	{
//		printf("ERROR: This program must be started with commandline arguments, for example:\n\n");
//		printf("   client abcdefghi    \n\n");
//		printf(" arg(abcdefghi): string to send to server\n"); //to make it
//		//easy, let's not bother handling spaces
//		exit(EXIT_FAILURE);
//	}


	//get a handle to the server app
	server_coid = name_open("myapp",0);

	printf("name server opened coid = %d\n",server_coid );

	//Create a channel for the process
	chid = ChannelCreate(0);

	printf("chid %d, created\n",chid);

	//since we are passing our own chid , we get a connection id to us
	self_coid = ConnectAttach(0,0,chid,_NTO_SIDE_CHANNEL,flags);

	printf("self coid created %d \n",self_coid);

	//terminate if failed
	if (server_coid == -1)
	{ //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		name_close(server_coid);
		exit(EXIT_FAILURE);
	}

	puts("creating pulse signal\n");


	SIGEV_PULSE_INIT(&msg.event,self_coid,10,PULSE_1,NULL);

	SIGEV_MAKE_UPDATEABLE(&msg.event);

	puts("MsgRegisterEvent pre\n");
	MsgRegisterEvent(&msg.event,server_coid);
	puts("MsgRegisterEvent post\n");
	MsgSend(server_coid,&msg,sizeof(msg),&rmsg,sizeof(rmsg));
	puts("MsgSend post\n");

	while(1)
	{
		rcvid = MsgReceive(chid,&rmsg,sizeof(rmsg),NULL);
		puts("MsgReceive post\n");
	}

	puts("name close\n");
	name_close(server_coid);
	return EXIT_SUCCESS;
}

