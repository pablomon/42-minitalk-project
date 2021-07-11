#include "minitalk.h"
#define SLEEP_TIME 300

void	send_bits(int pid, char **msg)
{
	int		signum;
	int		ret;
	uint	byte[8];
	int		i;

	i = 0;
	while (**msg)
	{
		//printf("%c\t", **msg);
		signum = SIGUSR1;
		if (**msg == '1')
			signum = SIGUSR2;
		if (kill(pid, signum) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		// byte[i%8] = **msg - 48;
		// printf("%d\n", byte[i%8]);
		 if (i%8 == 0)
		// {
		 	ft_putstr(".");
		// 	printf("%c", binary2char(byte));
		// }
		i++;
		*msg = *msg + 1;
		usleep(SLEEP_TIME);
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
	//printf("%s\n", dest);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;
	int		len;
	char	*encoded;
	char	*p_malloc;
	int		end;

	input_check(argc, argv);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	p_malloc = (char *)(malloc(sizeof(int) * (sizeof(uint) * 8 + 8 * len)));
	errno = 0;
	encoded = p_malloc;
	int2binary(ft_strlen(argv[2]), encoded);
	//printf("%s\n", encoded);
	put_data(argv[2], encoded + sizeof(uint) * 8);
	//printf("%s\n", encoded);
	printf("Sending bits:\n");
	send_bits(pid, &encoded);
	printf("\nMessage sent\n");
	free(p_malloc);
	return (0);
}
