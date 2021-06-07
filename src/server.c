#include "minitalk.h"

int g_client;

int decode_int(unsigned int *b)
{
	int				i = 0;
	unsigned int	integer = 0;

	while (i < sizeof(unsigned int) * 8)
	{
		if (b[i] == 1)
		{
			integer += 0x1 << i;
		}
		i++;
	}
	return integer;
}

char binary2char(unsigned int *b)
{
	int				i = 0;
	unsigned char	c = 0;

	while (i < 8)
	{
		if (b[i] == 1)
			c += 0x1 << i;
		i++;
	}

	printf("%c, ", c);
	return c;
}


unsigned int* header_bit(unsigned int value, int reset)
{
	static unsigned int header[64];
	static int i;

	if (reset == 1)
	{
		ft_memset(header, 0, sizeof(header));
		i = 0;
		return (0);
	}

	printf("Header bit: %d\n", value);

	header[i] = value;
	i++;
	return (&header[0]);
}

void decode_msg(unsigned int *bin, int len)
{
	int i;
	int j;
	unsigned int binary_char[8];
	char *msg;

	i = 0;
	msg = (char*)(malloc(sizeof(char) * (len + 1)));
	while (i < len)
	{
		j = 0;
		while (j < 8)
		{
			binary_char[j] = bin[i*8 + j];
			j++;
		}
		msg[i] = binary2char(binary_char);
		i++;
	}
	msg[i] = 0;
	printf("Decoded message: %s\n", msg);
	header_bit(0, 1); // reset header
	free (msg);
}


void bit_received(unsigned int value)
{
	static int bit_num;
	static int msg_len = 65;
	static unsigned int msg[1000]; // todo pasar a list

	printf("[bit %d]", bit_num);
	//first 64bits are for the length of the message
	if (bit_num < (INT_BITS - 1))
		header_bit(value, 0);
	else if (bit_num == INT_BITS - 1)
	{
		msg_len = decode_int(header_bit(value, 0));
		printf("message length: %u\n", msg_len);
	}
	else if (bit_num - INT_BITS < msg_len * 8 - 1)
	{
		printf("Message bit: %d\n", value);
		msg[bit_num - INT_BITS] = value;
	}
	else // msg finished
	{
		printf("Last message bit: %d\n", value);
		msg[bit_num - INT_BITS] = value;
		decode_msg(msg, msg_len);
	}

	bit_num++;
}

void handling_function(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGUSR1)
		bit_received(0);
	if (signum == SIGUSR2)
		bit_received(1);


	//int ret = kill(info->si_pid, SIGUSR1);

	int ret = kill(g_client, SIGUSR1);
	if (ret == -1)
		perror("error");

}

void test()
{
	bit_received(1);
	for (size_t i = 0; i < 31; i++)
	{
		bit_received(0);
	}
	bit_received(1);
	bit_received(0);
	bit_received(0);
	bit_received(0);
	bit_received(0);
	bit_received(1);
	bit_received(1);
	bit_received(0);
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;
	sa.sa_handler = &handling_function;
	//sa_1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid_t pid = getpid();
	printf("pid %d\nListening...\n", pid);

	//test();

	printf("Client pid?");
	scanf("%d", &g_client);

	while (1>0)
	{
		sleep(1);
	}

	return 0;
}
