/*
 * Sample Structure _msg_info64 values:
nd: 0
srcnd: 0
pid: 74797077
tid: 1
chid: 1
scoid: 65537
coid: 1073741825
priority: 10
flags: 4096
msglen: 8
srcmsglen: 8
dstmsglen: 8
type_id: 0
reserved: 0
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include "message.h"
#include <errno.h>

void print_msg_info64(const struct _msg_info64 *info);

int main(void) {
	int chid;
	rcvid_t rcvid;
	mymsg_t msg;
	mymsg_t reply_msg;
	struct _msg_info info;
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
		rcvid = MsgReceive(chid,&msg,sizeof(msg),&info);
		puts("Received message!!!");
		//alternate msg info fects
		//MsgInfo(rcvid,&info);
		print_msg_info64(&info);
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


// Function to print the structure
void print_msg_info64(const struct _msg_info64 *info) {
    if (info == NULL) {
        printf("Invalid structure pointer (NULL).\n");
        return;
    }

    printf("Structure _msg_info64 values:\n");
    printf("nd: %u\n", info->nd);
    printf("srcnd: %u\n", info->srcnd);
    printf("pid: %d\n", info->pid);
    printf("tid: %d\n", info->tid);
    printf("chid: %d\n", info->chid);
    printf("scoid: %d\n", info->scoid);
    printf("coid: %d\n", info->coid);
    printf("priority: %d\n", info->priority);
    printf("flags: %d\n", info->flags);
    printf("msglen: %lld\n", (long long)info->msglen);
    printf("srcmsglen: %lld\n", (long long)info->srcmsglen);
    printf("dstmsglen: %lld\n", (long long)info->dstmsglen);
    printf("type_id: %u\n", info->type_id);
    printf("reserved: %u\n", info->reserved);
}
