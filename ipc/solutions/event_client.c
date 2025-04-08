/*
 * event_client.c
 * 
 * This program, along with event_server.c, demonstrate pulses between a
 * server and a client using MsgDeliverEvent().
 * 
 * The client finds the server using name_open(), passing it the name the 
 * server has registered with name_attach().
 * 
 * The code to set up the event structure for sending to the server has 
 * been removed, you will need to fill it in.
 * 
 *  To test it, first run event_server and then run the client as follows:
 *    event_client
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <pthread.h>

#include "event_server.h"
#include <unistd.h>

// this is the pulse code we'll expect from the server when it notifies us
#define MY_PULSE_CODE (_PULSE_CODE_MINAVAIL + 3)

union recv_msg
{
	struct _pulse pulse;
	short type;
} recv_buf;

int server_locate()
{
    int server_coid;

    server_coid = name_open(RECV_NAME, 0);

    while (server_coid == -1)
    {
        sleep(1);
        server_coid = name_open(RECV_NAME, 0);
    }

    return server_coid;
}

int main(int argc, char *argv[])
{
	int server_coid, self_coid, chid;
	rcvid_t rcvid;
	struct notification_request_msg msg;
	struct sched_param sched_param;

	// create a channel on the client for getting pulses from the server
	chid = ChannelCreate( _NTO_CHF_PRIVATE );
	if (chid == -1)
	{
		perror("ChannelCreate");
		exit(EXIT_FAILURE);
	}

	/* look for server */
	server_coid = server_locate();

	// create a connection to our own channel for the pulse event structure
	self_coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (self_coid == -1)
	{
		perror("ConnectAttach");
		exit(EXIT_FAILURE);
	}

	msg.type = REQUEST_NOTIFICATIONS;

	/* Initialize the sigevent structure (msg.ev) in the message
	 * to be sent to the server.
	 */

	pthread_getschedparam(0, NULL, &sched_param );

	SIGEV_PULSE_INIT( &msg.ev, self_coid, sched_param.sched_priority, MY_PULSE_CODE, 0 );
	// optional - make this updateable to tell server it can modify it
	SIGEV_MAKE_UPDATEABLE( &msg.ev );

	/* register the event (msg.ev) in the message to be sent to the server.
     */
	if( MsgRegisterEvent(&msg.ev, server_coid) == -1) {
        perror("MsgRegisterEvent");
        exit(EXIT_FAILURE);
	}

	// send our registration message to the server
	if (MsgSend(server_coid, &msg, sizeof(msg), NULL, 0) == -1)
	{
		perror("MsgSend");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		// wait for messages or pulses, we only expect pulses
		rcvid = MsgReceive(chid, &recv_buf, sizeof(recv_buf), NULL );
		if (rcvid == -1)
		{
			perror("MsgReceive");
			exit(EXIT_FAILURE);
		}
		if (rcvid == 0)
		{
			if (MY_PULSE_CODE == recv_buf.pulse.code)
			{
				printf("got my pulse, value is %d\n", recv_buf.pulse.value.sival_int);
			}
			else
			{
				printf("got unexpected pulse with code %d\n", recv_buf.pulse.code);
			}
			continue;
		}
		// This case should never happen, since we set _NTO_CHF_PRIVATE
		printf("got unexpected message, type: %d\n", recv_buf.type);
		if (MsgError(rcvid, ENOSYS) == -1)
		{
			perror("MsgError");
		}
	}
}
