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
	int coid; //Connection ID to server
	rx_msg_t msg;
	int incoming_checksum; //space for server's reply
	int status; //status return value used for MsgSend
	//int server_pid; //server's process ID
	//int server_chid; //server's channel ID

	if (argc != 2)
	{
		printf("ERROR: This program must be started with commandline arguments, for example:\n\n");
		printf("   client abcdefghi    \n\n");
		printf(" arg(abcdefghi): string to send to server\n"); //to make it
		//easy, let's not bother handling spaces
		exit(EXIT_FAILURE);
	}

//	printf("attempting to establish connection with server pid: %d, chid %d\n", server_pid,
//			server_chid);

	//PUT CODE HERE to establish a connection to the server's channel, store the
	//connection id in the variable 'coid'
	//coid = ConnectAttach(0, server_pid, server_chid, _NTO_SIDE_CHANNEL, 0);

	coid = name_open("myapp",0);




	if (coid == -1)
	{ //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		name_close(coid);
		exit(EXIT_FAILURE);
	}

	msg.msg_type = CKSUM_MSG_TYPE;
	strlcpy(msg.csum.string_to_cksum, argv[1], sizeof(msg.csum.string_to_cksum));
	printf("Sending string: %s\n", msg.csum.string_to_cksum);

	status = MsgSendPulse(coid, -1, 3, 0xdeadc0de);
	if (status == -1)
	{
		perror("MsgSendPulse");
	}

	//PUT CODE HERE to send message to server and get the reply
	status = MsgSend(coid, &msg, sizeof(msg), &incoming_checksum,
			sizeof(incoming_checksum));
	if (status == -1)
	{ //was there an error sending to server?
		perror("MsgSend");
		name_close(coid);
		exit(EXIT_FAILURE);
	}

	printf("received checksum=%d from server\n", incoming_checksum);
	printf("MsgSend return status: %d\n", status);
	name_close(coid);
	return EXIT_SUCCESS;
}

