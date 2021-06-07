#include "minitalk.h"

void handling_function(int signum)
{

	printf("Signal received %d\n", signum);
	if (signum == SIGUSR1)
	{
		// ack
	}
}

int input_check(int argc, char const *argv[])
{

}

int main(int argc, char const *argv[])
{	
	pid_t pid;
	struct sigaction sa_1;

	input_check(argc, &)

	sa_1.sa_handler = &handling_function;
	sa_1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_1, NULL);

	pid = ft_atoi(argv[1]);
	char *encoded = (char*)(malloc(sizeof(unsigned int) * 8 * ft_strlen(argv[2])));
	errno = 0;

    // encode(argv[2], &encoded);
    // send_bit(pid, &encoded);


	return 0;
}
