#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

volatile int produce=0;


void process_rx(void)
{
	static volatile unsigned var3;

	var3++;
	/* For faster/slower processors, may need to tune this program by
	 * modifying the frequency of this printf -- add/remove a 0
	 * 10000000
	 */
	if (!(var3 % 100000))
		printf("thread %d did some work\n", pthread_self());
}

void * transmit(void *arg)
{
	static int count=10;
	while(1)
	{
		//step 1 lock the mutex
		pthread_mutex_lock(&mut);
		//step 2 check the data is consumed ?
		while(produce ==1)
		{
			//step 3 wait forever
			//setp 3.1 check for the flag and release mutex but block the thread.
			pthread_cond_wait(&cond,&mut);
		}
		// step 4 we are here means we got a signal from the receive thread and mutex context
		// we have to transmit the next data

		produce =1;
		//step 5 signal to the receive thread
		pthread_cond_signal(&cond);
		//step 6 always release mutex
		pthread_mutex_unlock(&mut);
		printf("Transmitted..\n");
		//test
		//sleep(1);

	}
}

void * receive(void *arg)
{
	while(1)
	{
		//step 1 lock the mutex
		pthread_mutex_lock(&mut);
		//step 2 check if data available
		while (produce == 0)
		{
			//step 2.1 if no data wait here (relase mutex but block thread)
			pthread_cond_wait(&cond,&mut);
		}
		//step 3 we hare here because we got data to process and inside a mutex now
		//step 4 process it
		produce = 0;
		//step 5 signal to transmit that we are done with the data
		pthread_cond_signal(&cond);
		//step 6 release the mutex
		pthread_mutex_unlock(&mut);
		process_rx();
		printf("Received..\n");
		//test
		sleep(3);
	}
	//never expected here
	return 0;
}


int main(void) {
	printf("Starting main\n");
	pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(NULL,NULL,transmit,NULL);
    //pthread_create(NULL,NULL,receive,NULL);
    //sleep(20);
    receive(NULL);
	return EXIT_SUCCESS;
}
