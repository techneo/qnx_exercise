#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// this is the argument passed to the child process
char *argv[] = {"echo", "Hello from the spawned process!", NULL};

int main(void) {
	pid_t child_pid;
	int ret;
	int status;

	//spawn the child process
	ret = posix_spawn (&child_pid, "/data/home/root/hello", NULL, NULL, &argv[0], NULL);
	if (ret != 0)
	{
	    printf("posix_spawn() failed: %s\n", strerror(ret) );
	    return EXIT_FAILURE;
	}

	//print child process id
	printf ("Child pid: %d\n\n", child_pid);
    // Wait for the spawned process to terminate

    if (waitpid(child_pid, &status, 0) == -1) {
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }
    //macro to check the value of status
    if (WIFEXITED(status)) {
        printf("Spawned process exited with status %d\n", WEXITSTATUS(status));
    }

    //will not run until the child is done
	while(1)
	{
		printf ("Child pid running: %d\n\n", child_pid);
		sleep(2);

	}
}
