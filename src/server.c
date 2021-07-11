#include "minitalk.h"

uint	*do_header_bit (uint value)
{
	static uint	header[INT_BITS];
	static int	i;

	if (i == 0)
	{
		ft_memset(header, 0, sizeof(header));
	}
	header[i] = value;
	if (i == INT_BITS - 1)
	{
		i = -1;
	}
	i++;
	return (&header[0]);
}

void	enqueu_bit(t_list *lst, uint value)
{
	uint	*v;
	t_list	*link;
	uint	*ui;

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

int	do_msg_bit(uint value, uint msg_len)
{
	static int		i;
	static t_list	*lst;

	if (lst == NULL) // reset
	{
		lst = ft_lstnew(NULL);
		i = 0;
	}
	enqueu_bit(lst, value);
	if (i == msg_len * 8 - 1)
	{
		decode_msg(lst, msg_len);
		null_list(lst);
		lst = NULL;
		i = 0;
		return (1);
	}
	i++;
	return (0);
}

// void	handling_function(int signum, siginfo_t *info, void *context)
void handling_function(int signum)
{
	static int	bits_received;
	static uint	msg_len;
	int			bit_val;

	if (signum == SIGUSR1)
		bit_val = 0;
	else if (signum == SIGUSR2)
		bit_val = 1;
	else
	{
		printf("Signal received not USER1 or USER2\n");
		exit(1);
	}
	if (bits_received < INT_BITS - 1)
		do_header_bit(bit_val);
	else if (bits_received == INT_BITS - 1)
	{
		msg_len = binary2int(do_header_bit(bit_val));
	}
	else
		if (do_msg_bit(bit_val, msg_len))
		{
			ft_putstr("\n\n");
			bits_received = -1;
		}
	bits_received++;
}

int	main(int argc, char const *argv[])
{
	struct sigaction	sa;
	pid_t				pid;

	// sa.sa_handler = &handling_function;
	//sa_1.sa_flags = SA_RESTART;
	// sigaction(SIGUSR1, &sa, NULL);
	// sigaction(SIGUSR2, &sa, NULL);
	signal(SIGUSR1, &handling_function);
	signal(SIGUSR2, &handling_function);
	pid = getpid();
	printf("pid %d\nListening:\n", pid);
	while (1 > 0)
	{
		sleep(1);
	}
	return (0);
}
