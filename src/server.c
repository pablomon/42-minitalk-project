#include "minitalk.h"

void handling_function(int signum, siginfo_t *info, ucontext_t *context)
{
	printf("Signal received %d from pid %d\n", signum, info->si_pid);
	int ret = kill(info->si_pid, SIGUSR1);
	if (ret == -1)
	 	perror("error");
}



int main(int argc, char const *argv[])
{
	struct sigaction sa_1;
	sa_1.sa_handler = &handling_function;
	sa_1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_1, NULL);

	struct sigaction sa_2;
	sa_2.sa_handler = &handling_function;
	sa_2.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa_2, NULL);

	pid_t pid = getpid();
	printf("pid %d\nListening...\n", pid);

	while (1>0)
	{
		sleep(1);
	}

	return 0;
}
