#include "minitalk.h"

// int	g_client;

uint	*header_bit (uint value, int reset)
{
	static uint	header[64];
	static int	i;

	if (reset == 1)
	{
		ft_memset(header, 0, sizeof(header));
		i = 0;
		return (0);
	}
	header[i] = value;
	i++;
	return (&header[0]);
}

void	enqueu_bit(t_list *lst, uint value)
{
	uint		*v;
	t_list		*link;
	uint		*ui;

	v = (uint *)(malloc(sizeof(uint)));
	*v = value;
	if (lst->content == NULL)
		lst->content = v;
	else
	{
		link = ft_lstnew(v);
		ui = link->content;
		ft_lstadd_back(&lst, ft_lstnew(v));
	}
}

void	bit_received(uint value, int pid)
{
	static int		bit_num;
	static int		msg_len;
	static t_list	*lst;

	if (lst == NULL) // reset
	{
		lst = ft_lstnew(NULL);
		bit_num = 0;
		header_bit(0, 1);
	}
	//first 64bits are for the length of the message
	if (bit_num < (INT_BITS - 1))
		header_bit(value, 0);
	else if (bit_num == INT_BITS - 1)
	{
		msg_len = binary2int(header_bit(value, 0));
		printf("Receiving %d characters long message...\n", msg_len);
	}
	else if (bit_num - INT_BITS < msg_len * 8 - 1)
		enqueu_bit(lst, value);
	else // msg finished
	{
		enqueu_bit(lst, value);
		decode_msg(lst, msg_len);
		null_list(lst);
		lst = NULL;
	}
	bit_num++;
}

void	handling_function(int signum, siginfo_t *info, void *context)
{
	int	pid;
	int	ret;
	
	// pid = g_client;
	pid = info->si_pid;
	if (signum == SIGUSR1)
		bit_received(0, pid);
	if (signum == SIGUSR2)
		bit_received(1, pid);
	ret = kill(pid, SIGUSR1);
	if (ret == -1)
		perror("error");
}

int	main(int argc, char const *argv[])
{
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_handler = &handling_function;
	//sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("pid %d\nListening...\n", pid);
	while (1)
		pause();
	return (0);
}
