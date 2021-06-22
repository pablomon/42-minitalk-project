#include "minitalk.h"

int	send_bit(int set_pid, char **set_encoded)
{
	static char	**buf;
	static int	pid;
	int			signum;
	int			ret;

	if (set_encoded != NULL)
		buf = set_encoded;
	if (set_pid != 0)
		pid = set_pid;
	if (**buf)
	{
		printf("%c\t", **buf);
		signum = SIGUSR1;
		if (**buf == '1')
			signum = SIGUSR2;
		ret = kill(pid, signum);
		if (ret == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		*buf = *buf + 1;
		return (0);
	}
	return (1);
}

void	handling_function(int signum, siginfo_t *info, void *context)
{
	int	end;

	if (signum == SIGUSR1)
	{
		printf("ack\n");
		end = send_bit(0, NULL);
		if (end == 1)
		{
			printf("\nMessage sent\n");
			exit(0);
		}
	}
}

void	input_check(int argc, const char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: client pid message\n");
		exit(EXIT_SUCCESS);
	}
	//if (argv[1] not a number)
		// printf("pid entered is not a number\n");
		// exit(EXIT_SUCCESS);
}

void	put_data(const char *msg, char *dest)
{
	char	*p;

	p = dest;
	while (*msg)
	{
		char2binary(*msg, p);
		p += 8;
		msg++;
	}
	printf("%s\n", dest);
}

int	main(int argc, char const *argv[])
{
	struct sigaction	sa;
	pid_t				pid;
	int					len;
	char				*encoded;
	char				*p_malloc;

	printf("client pid: %d\n", getpid());
	input_check(argc, argv);
	sa.sa_handler = &handling_function;
	//sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	p_malloc = (char *)(malloc(sizeof(int) * (sizeof(uint) * 8 + 8 * len)));
	errno = 0;
	encoded = p_malloc;
	int2binary(ft_strlen(argv[2]), encoded);
	printf("%s\n", encoded);
	put_data(argv[2], encoded + sizeof(uint) * 8);
	printf("%s\n", encoded);

	printf("Server pid?");
	scanf("%d", &pid);

	printf("Sending bits:\n");
	send_bit(pid, &encoded);
	while (1 > 0)
		sleep(1);
	free(p_malloc);
	return (0);
}
