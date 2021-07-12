#include "minitalk.h"
#define SLEEP_TIME 100

void	send_bits(int pid, char *str)
{
	int		signum;
	int		ret;
	uint	byte[8];
	int		i;
	char	*ptr;

	i = 0;
	ptr = str;
	while (*ptr)
	{
		signum = SIGUSR1;
		if (*ptr == '1')
			signum = SIGUSR2;
		if (kill(pid, signum) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		if (i%8 == 0)
		ft_putstr(".");
		i++;
		ptr++;
		usleep(SLEEP_TIME);
	}
}

void	send_header(int pid, int len)
{
	char	header[INT_BITS + 1];

	ft_bzero(header, INT_BITS + 1);
	int2binary(len, header);
	send_bits(pid, header);
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
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;
	int		len;
	char	*p_msg;
	int		end;

	input_check(argc, argv);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	send_header(pid, len);
	p_msg = (char *)(malloc(sizeof(int) * 8 * len));
	put_data(argv[2], p_msg);	
	printf("Sending bits:\n");
	send_bits(pid, p_msg);
	printf("\nMessage sent\n");
	free(p_msg);
	return (0);
}
