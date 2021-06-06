#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "minitalk.h"

void binary2char(char *b)
{
	int				i = 0;
	unsigned char	c = 0;

	while (i < 8)
	{
		if (b[i] == '1')
			c += 0x1 << i;
		i++;
	}
	printf("%c\n", c);
}

void char2binary(char c)
{
	int	i = 0;

	char b[8] = "";
	while (i < 8)
	{
		unsigned char d = 0x1 & c >> i;
		if (d == 0)
			b[i] = '0';
		else
			b[i] = '1';
		i++;
	}
	printf("%s\n", b);
	binary2char(b);
}

void binary2int(char *b)
{
	int				i = 0;
	unsigned int	integer = 0;

	while (i < sizeof(unsigned int) * 8)
	{
		if (b[i] == '1')
			integer += 0x1 << i;
		i++;
	}
	printf("%u\n", integer);
}

void int2binary(unsigned int n, char *str)
{
	int	i = 0;

	while (i < sizeof(unsigned int) * 8)
	{
		unsigned char d = 0x1 & n >> i;
		if (d == 0)
			str[i] = '0';
		else
			str[i] = '1';
		i++;
	}

}

void handling_function(int signum)
{
	printf("Signal received %d\n", signum);
}

void send_string(char *str, pid_t pid)
{
	printf("%s\n", str);
	binary2int(str);

	char *p;

	p = str;
	while (*p!=0)
	{
		if (*p == '0')
		{
			printf("0");
			kill(pid, SIGUSR1);
		}
		else
			printf("1");
			kill(pid, SIGUSR2);
		p++;
	}
}

int main(int argc, char const *argv[])
{
	errno = 0;

	pid_t pid = ft_atoi(argv[1]);

	char *msg_len = (char*)(malloc(sizeof(unsigned int) * 8));

	int2binary(ft_strlen(argv[2]), &msg_len);
	//send_string(&msg_len, pid);
	int ret = kill(pid, SIGUSR2);
	if (ret == -1)
	{
	 	perror("error");
	}

	return 0;
}

