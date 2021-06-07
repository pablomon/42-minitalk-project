#include "minitalk.h"

int send_bit(int set_pid, char **set_encoded)
{
    static char **buf;
    static int  pid;
    int     signum;

    if (set_encoded != NULL)
        buf = set_encoded;
    if (set_pid != 0)
        pid = set_pid;

	printf("Sending bit (%s)\n", *buf);

    if (**buf)
    {
		printf("%c\n", **buf);
	    signum = SIGUSR1;
        if (**buf == '1')
            signum = SIGUSR2;
        int ret = kill(pid, signum);
        if (ret == -1)
        {
            perror("error");
            exit(EXIT_FAILURE);
        }
		*buf = *buf + 1;
        return (0);
    }
    else
        return(1);
}

void handling_function(int signum, siginfo_t *info, void *context)
{
    int end;

	if (signum == SIGUSR1)
    {
        printf("ack received");
        end = send_bit(0, NULL);
        if (end == 1)
        {
            printf("message sent");
            exit(0);
        }
    }
}

void input_check(int argc, const char *argv[])
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

void char2binary(char c, char *dest)
{
	int	i = 0;

	while (i < 8)
	{
		unsigned char d = 0x1 & c >> i;
		if (d == 0)
			dest[i] = '0';
		else
			dest[i] = '1';
		i++;
	}
}

void put_data(const char *msg, char *dest)
{
    char *p = dest;
    while (*msg)
    {
        char2binary(*msg, p);
        p+=8;
        msg++;
    }

	printf("%s\n", dest);
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

void put_header(int len, char *dest)
{
	int2binary(len, dest);
	printf("%s\n", dest);
}

int main(int argc, char const *argv[])
{
	printf("client pid: %d\n", getpid());
	pid_t pid;
	struct sigaction sa;
	char *encoded;
	char *p_malloc;

	input_check(argc, argv);

	sa.sa_handler = &handling_function;
	//sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);

	pid = ft_atoi(argv[1]);
	p_malloc = (char*)(malloc(sizeof(int) * (sizeof(unsigned int) * 8 + 8 * ft_strlen(argv[2]))));
	errno = 0;

	encoded = p_malloc;

	put_header(ft_strlen(argv[2]), encoded);


	put_data(argv[2], encoded + sizeof(unsigned int) * 8);
	printf("%s\n", encoded);

	printf("Server pid?");
	scanf("%d", &pid);

	send_bit(pid, &encoded);

	while (*encoded)
	{
		sleep(1);
	}

	free(p_malloc);
	return 0;
}
