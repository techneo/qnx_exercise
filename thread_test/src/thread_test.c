#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t *tid;
pthread_attr_t attr;
struct sched_param param;

void * thread_fn(void * param)
{
	while(1)
	{
		puts("Hello thread!!!"); /* prints Hello World!!! */
		sleep(1);
	}
}

int main(void) {
	puts("Hello World!!!"); /* prints Hello World!!! */

	//init a blank attribute structure
	pthread_attr_init(&attr);

	//to enable to change the sched params
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	param.sched_priority=15;
	// to change the priority
	pthread_attr_setschedparam(&attr,&param);
	// to change the sched policy from default
	pthread_attr_setschedpolicy(&attr,SCHED_FIFO  );

	// to increase the stack size
	// must be greater than PTHREAD_STACK_MIN (4k)
	pthread_attr_setstacksize(&attr,256*1024);

	//create thread1
	pthread_create(tid,&attr,&thread_fn,NULL);
	//create thread2
	pthread_create(tid,&attr,&thread_fn,NULL);
	while(1)
	{
		puts("Hello Process!!!");
		sleep(1);
	}
	return EXIT_SUCCESS;
}
