#include "minitalk.h"

void	print_chars(t_uint bitval)
{
	static int		i;
	static t_uint	byte[8];
	char			c;

	byte[i] = bitval;
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
		write(1, &c, 1);
	}
	i++;
}

void	free_link(void *content)
{
	free(content);
}

void	null_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_lstclear(&lst, free_link);
	free(lst);
	lst = NULL;
}

void	received(char *msg, pid_t pid)
{
	printf("\n\nPrinting message received:\n%s\n\n", msg);
	kill(pid, SIGUSR2);
	printf("pid %d\nlistening\n", getpid());
}

void	decode_msg(t_list *lst, int len, pid_t client_pid)
{
	int		i;
	int		j;
	t_uint	binary_char[8];
	char	*msg;
	t_list	*ptrlst;

	ptrlst = lst;
	i = 0;
	msg = (char *)(malloc(sizeof(char) * (len + 1)));
	while (i < len)
	{
		j = 0;
		while (j < 8)
		{
			binary_char[j] = *((t_uint *)(ptrlst->content));
			j++;
			ptrlst = ptrlst->next;
		}
		msg[i] = binary2char(binary_char);
		i++;
	}
	msg[i] = 0;
	received(msg, client_pid);
	free (msg);
	null_list(lst);
}
