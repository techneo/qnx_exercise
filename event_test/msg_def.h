#ifndef _MSG_DEF_H_
#define _MSG_DEF_H_

#include <sys/iomsg.h>

#define MAX_STRING_LEN    256
// values less than _IO_MAX(511) are not to be used
// as these are messag ids reserved by QNX system libraries
#define CKSUM_MSG_TYPE (_IO_MAX + 1)

//layout of msgs should always defined by a struct, and ID'd by a msg type
// number as the first member

struct csum_t
{
	uint16_t msg_type;
	char string_to_cksum[MAX_STRING_LEN +1];
};
typedef struct
{
	//always the first element
	uint16_t msg_type;
	char string_to_cksum[MAX_STRING_LEN + 1]; //ptr to string we're sending to server, to make it
} cksum_msg_t; //easy, server assumes a max of 256 chars!!!!


typedef union
{
	//always the first element
	uint16_t msg_type;
	struct _pulse pulse;
	struct sigevent event;
	struct csum_t csum;
}rx_msg_t;


typedef union
{
	//always the first element
	uint16_t msg_type;
	struct _pulse pulse;
	struct sigevent event;
	struct csum_t csum;
}tx_msg_t;

// checksum reply is an int

// If you are sharing a target with other people, please customize these server names
// so as not to conflict with the other person.

#define CKSUM_PULSE_CODE (_PULSE_CODE_MINAVAIL+3)

#define SERVER_NAME		"cksum_server"  

#define DISCONNECT_SERVER "disconnect_server"

#define UNBLOCK_SERVER "unblock_server"

#define MSG_TYPE_INVALID -1
#define MSG_TYPE_PULSE 0

#define PULSE_1 1

#endif //_MSG_DEF_H_
