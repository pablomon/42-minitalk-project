#include "minitalk.h"

t_uint	*header_bit (t_uint value, int reset)
{
	static t_uint	header[64];
	static int		i;

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

void	enqueu_bit(t_list *lst, t_uint value)
{
	t_uint		*v;
	t_list		*link;

	print_chars(value);
	v = (t_uint *)(malloc(sizeof(t_uint)));
	*v = value;
	if (lst->content == NULL)
		lst->content = v;
	else
	{
		link = ft_lstnew(v);
		ft_lstadd_back(&lst, link);
	}
}

void	bit_received(t_uint value, int pid)
{
	static unsigned long	bit_num;
	static unsigned long	msg_len;
	static t_list			*lst;

	if (bit_num == 0)
	{
		lst = ft_lstnew(NULL);
		header_bit(0, 1);
	}
	if (bit_num < (sizeof(unsigned int) * 8 - 1))
		header_bit(value, 0);
	else if (bit_num == sizeof(unsigned int) * 8 - 1)
	{
		msg_len = binary2int(header_bit(value, 0));
		printf("Receiving %lu characters long message...\n", msg_len);
	}
	else
		enqueu_bit(lst, value);
	if (bit_num - sizeof(unsigned int) * 8 == msg_len * 8 - 1)
	{
		decode_msg(lst, msg_len, pid);
		bit_num = -1;
	}
	bit_num++;
}

void	handling_function(int signum, siginfo_t *info, void *context)
{
	int	ret;

	(void)context;
	if (signum == SIGUSR1)
		bit_received(0, info->si_pid);
	if (signum == SIGUSR2)
		bit_received(1, info->si_pid);
	ret = kill(info->si_pid, SIGUSR1);
	if (ret == -1)
		perror("error");
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handling_function;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	printf("pid %d\nlistening\n", getpid());
	while (1)
		pause();
}
