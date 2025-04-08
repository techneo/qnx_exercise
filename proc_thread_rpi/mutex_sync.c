/*
 *  mutex_sync.c
 *
 *  This code is the same as nomutex.c.
 *
 *  The exercise is to use the mutex construct that we learned
 *  about to modify the source to prevent our access problem.
 *
 */

#include <stdio.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <atomic.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 *  The number of threads that we want to have running
 *  simultaneously.
 */

#define NUMTHREADS      4

/*
 *  the global variables that the threads compete for.
 *  To demonstrate contention, there are two variables
 *  that have to be updated "atomically".  With RR
 *  scheduling, there is a possibility that one thread
 *  will update one of the variables, and get preempted
 *  by another thread, which will update both.  When our
 *  original thread runs again, it will continue the
 *  update, and discover that the variables are out of
 *  sync.
 *
 *      Note: Error checking has been left out in much of this example
 *      to increase readability.  Production code should not leave out
 *      this error checking.
 */

volatile unsigned var1;
volatile unsigned var2;

//must be a global variable
pthread_mutex_t my_mutex;

void *update_thread(void *);

volatile int done;

int main()
{
	int ret;

	pthread_t threadID[NUMTHREADS]; // a place to hold the thread ID's
	pthread_attr_t attrib; // scheduling attributes
	struct sched_param param; // for setting priority
	int i, policy;

	var1 = var2 = 0; /* initialize to known values */

	pthread_mutex_init(&my_mutex,NULL);

	printf("mutex_sync:  starting; creating threads\n");

	/*
	 *  we want to create the new threads using Round Robin
	 *  scheduling, and a lowered priority, so set up a thread
	 *  attributes structure.  We use a lower priority since these
	 *  threads will be hogging the CPU
	 */

	ret = pthread_getschedparam(pthread_self(), &policy, &param);
	if ( ret != EOK )
	{
		fprintf(stderr, "pthread_getschedparam failed: %s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}

	ret = pthread_attr_init(&attrib);
	if ( ret != EOK )
	{
		fprintf(stderr, "pthread_attr_init failed: %s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	ret = pthread_attr_setinheritsched(&attrib, PTHREAD_EXPLICIT_SCHED);
	if ( ret != EOK )
	{
		fprintf(stderr, "pthread_attr_setinheritsched failed: %s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	ret = pthread_attr_setschedpolicy(&attrib, SCHED_RR);
	if ( ret != EOK )
	{
		fprintf(stderr, "pthread_attr_setschedpolicy failed: %s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	param.sched_priority -= 2; // drop priority a couple levels
	ret = pthread_attr_setschedparam(&attrib, &param);
	if ( ret != EOK )
	{
		fprintf(stderr, "pthread_attr_setschedparam failed: %s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	/*
	 *  create the threads.  As soon as each pthread_create
	 *  call is done, the thread has been started.
	 */

	for (i = 0; i < NUMTHREADS; i++)
	{
		ret = pthread_create(&threadID[i], &attrib, &update_thread, 0);
		if ( ret != EOK )
		{
			fprintf(stderr, "pthread_create failed: %s\n", strerror(ret));
			exit(EXIT_FAILURE);
		}
	}

	/*
	 *  let the other threads run for a while
	 */

	sleep(15);

    /*
     * Tell the threads to exit.
     */

    done = 1;

    // wait for them to exit
    for (i = 0; i < NUMTHREADS; i++)
    {
        ret = pthread_join(threadID[i], NULL);
        if ( ret != EOK )
        {
            fprintf(stderr, "pthread_join failed: %s\n", strerror(ret));
            exit(EXIT_FAILURE);
        }
    }

	// all other threads are gone, so no need to lock var_mutex for var1 and var2 any longer
	printf("all done, var1 is %u, var2 is %u\n", var1, var2);

	printf("Effeciency = %3.2f\n", (double)var1/(double)582532586*(double)100);

	return EXIT_SUCCESS;
}

/*
 *  the actual thread.
 *
 *  The thread ensures that var1 == var2.  If this is not the
 *  case, the thread sets var1 = var2, and prints a message.
 *
 *  Var1 and Var2 are incremented.
 *
 *  Looking at the source, if there were no "synchronization" problems,
 *  then var1 would always be equal to var2.  Run this program and see
 *  what the actual result is...
 */

void do_work()
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

void *
update_thread(void *i)
{
	int mut_ret;
	while (!done)
	{
		//pass3
		mut_ret = pthread_mutex_lock(&my_mutex);
		if (EOK != mut_ret)
		{
			fprintf(stderr,"Failed locking mutex");
			exit(EXIT_FAILURE);
		}
		//pass2
		//pthread_mutex_lock(&my_mutex);
		if (var1 != var2)
		{
			int local_var1;
			int local_var2;
			local_var1=var1;
			local_var2=var2;
			//pass3
			mut_ret = pthread_mutex_unlock(&my_mutex);
			if (EOK != mut_ret)
			{
				fprintf(stderr,"Failed unlocking mutex");
				exit(EXIT_FAILURE);
			}
			//ensure that mutex is unlocked before calling any printfs
			//printf("thread %d, var1 (%u) is not equal to var2 (%u)!\n", pthread_self(), var1, var2);
			printf("thread %d, var1 (%u) is not equal to var2 (%u)!\n", pthread_self(), local_var1, local_var2);

			//we cant use var1,var2 without lock so create duplicates and store before coming here
			var1 = var2;
		}
		//pass3
		// just unlock mutex and go
		else
		{
			mut_ret = pthread_mutex_unlock(&my_mutex);
			if (EOK != mut_ret)
			{
				fprintf(stderr,"Failed unlocking mutex");
				exit(EXIT_FAILURE);
			}
		}
		//pass2
		//pthread_mutex_unlock(&my_mutex);

		/* do some work here */
		do_work();
		//pass1
		mut_ret = pthread_mutex_lock(&my_mutex);
		if (EOK != mut_ret)
		{
			fprintf(stderr,"Failed locking mutex");
			exit(EXIT_FAILURE);
		}
		var1 += 2;
		var1--;
		var2 += 2;
		var2--;
		//pass1
		mut_ret = pthread_mutex_unlock(&my_mutex);
		if (EOK != mut_ret)
		{
			fprintf(stderr,"Failed unlocking mutex");
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

