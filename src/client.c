#include "minitalk.h"
#define SLEEP_TIME 100

void print_char(int val)
{
	static	int i;
	static	uint byte[8];
	char c;

	byte[i] = (uint)val;
	if (i == 7)
	{
		i = 0;
		c = 0;
		while (i < 8)
		{
			if (byte[i] == 1)
				c += 0x1 << i;
			i++;
		}
		i = -1;

		printf("%c", c);
		//ft_putchar_fd(c, 1);
	}
	i++;
}

void	send_bits(int pid, char *str, int print)
{
	int		signum;
	char	*ptr;
	int		val;

	ptr = str;
	while (*ptr)
	{
		signum = SIGUSR1;
		val = 0;
		if (*ptr == '1')
		{
			signum = SIGUSR2;
			val = 1;
		}
		if (kill(pid, signum) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		if (print)
			print_char(val);
		ptr++;
		usleep(SLEEP_TIME);
	}
}

void	send_header(int pid, int len)
{
	char	header[INT_BITS + 1];

	ft_bzero(header, INT_BITS + 1);
	int2binary(len, header);
	send_bits(pid, header, 0);
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

void	send_msg(pid_t pid, const char *input)
{
	char	*msg;
	char	*ptr;

	msg = (char *)(malloc(sizeof(int) * 8 * ft_strlen(input)));
	ptr = msg;
	while (*input)
	{
		char2binary(*input, ptr);
		ptr += 8;
		input++;
	}
	send_bits(pid, msg, 1);
	free(msg);
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
	printf("Sending bits:\n");
	send_msg(pid, argv[2]);
	printf("\nMessage sent\n");
	return (0);
}
