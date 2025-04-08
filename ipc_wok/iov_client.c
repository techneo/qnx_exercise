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
#include "iov_server.h"

int main(int argc, char* argv[])
{
	int coid; //Connection ID to server
	//rx_msg_t msg;
	int incoming_checksum; //space for server's reply
	int status; //status return value used for MsgSend

	iov_t my_multipart_msg[2];
	char mmsg[50];
	iov_header_t msg_hdr;


	if (argc != 2)
	{
		printf("ERROR: This program must be started with commandline arguments, for example:\n\n");
		printf("   client abcdefghi    \n\n");
		printf(" arg(abcdefghi): string to send to server\n"); //to make it
		//easy, let's not bother handling spaces
		exit(EXIT_FAILURE);
	}

	incoming_checksum=0;
	coid = name_open("myapp",0);

	if (coid == -1)
	{ //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		name_close(coid);
		exit(EXIT_FAILURE);
	}

	//msg.msg_type = CKSUM_MSG_TYPE;
	strcpy(mmsg, argv[1]);

//	my_multipart_msg[0].iov_base = &mmsg_len;
//	my_multipart_msg[0].iov_len = sizeof(mmsg_len);
//
//	my_multipart_msg[1].iov_base = &mmsg;
//	my_multipart_msg[1].iov_len=sizeof(mmsg);

	msg_hdr.msg_type.msg_type=CKSUM_MSG_TYPE;
	msg_hdr.len=sizeof(mmsg);

	SETIOV(&my_multipart_msg[0],&msg_hdr,sizeof(msg_hdr));
	SETIOV(&my_multipart_msg[1],&mmsg,sizeof(mmsg));



	printf("Sending pulse: %d\n", 3);
	status = MsgSendPulse(coid, -1, 3, 0xdeadc0de);
	if (status == -1)
	{
		perror("MsgSendPulse");
	}


//	status = MsgSend(coid, &msg, sizeof(msg), &incoming_checksum,
//			sizeof(incoming_checksum));
	printf("Sending string: %s\n", mmsg);

	status = MsgSendvs(coid,my_multipart_msg,2,&incoming_checksum,sizeof(incoming_checksum));
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

