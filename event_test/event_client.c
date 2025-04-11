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
//	int incoming_checksum; //space for server's reply
//	int status; //status return value used for MsgSend



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

	//build the signal structure that has
	//the clients self coid that goes to the server
	//sets the priority as 10
	//delivers the puse PULSE_1
	SIGEV_PULSE_INIT(&msg.event,self_coid,10,PULSE_1,NULL);

	//this allows the server to change the data
	//inside the event structure
	SIGEV_MAKE_UPDATEABLE(&msg.event);

	puts("MsgRegisterEvent pre\n");
	//subscribing to the server with the event structure we built
	//as a secure event
	MsgRegisterEvent(&msg.event,server_coid);
	puts("MsgRegisterEvent post\n");
	//send message to the server process via its coid
	//message contains the event.
	//expecting a reply on the rmsg
	MsgSend(server_coid,&msg,sizeof(msg),&rmsg,sizeof(rmsg));
	puts("MsgSend post\n");
	//unblocked
	while(1)
	{
		//receive events and wait blocked till the event arrives
		rcvid = MsgReceive(chid,&rmsg,sizeof(rmsg),NULL);
		puts("MsgReceive post\n");
	}

	puts("name close\n");
	name_close(server_coid);
	return EXIT_SUCCESS;
}

