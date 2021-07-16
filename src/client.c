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

void	ack_bit(int signum)
{
	int		end;

	if (signum == SIGUSR1)
	{
		end = send_bit(0, NULL);
		if (end == 1)
		{
			printf("\nMessage sent\n");
			exit(EXIT_SUCCESS);
		}
	}
}

void	msg_received(int signum)
{
	(void)signum;
	printf("Server ack message received!\n");
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
}

int	main(int argc, char const *argv[])
{
	pid_t				pid;
	int					len;
	char				*encoded;
	char				*p_malloc;

	input_check(argc, argv);
	signal(SIGUSR1, ack_bit);
	signal(SIGUSR2, msg_received);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	p_malloc = (char *)(malloc(sizeof(int) * (sizeof(t_uint) * 8 + 8 * len)));
	encoded = p_malloc;
	int2binary(ft_strlen(argv[2]), encoded);
	put_data(argv[2], encoded + sizeof(t_uint) * 8);
	printf("Sending %d characteres long message...\n", len);
	send_bit(pid, &encoded);
	while (1)
	{
		pause();
	}
	free(p_malloc);
	return (EXIT_SUCCESS);
}
