#include "minitalk.h"

void	free_link(void *content)
{
	free(content);
}

void	null_list(t_list *lst)
{
	ft_lstclear(&lst, free_link);
	free(lst);
	lst = NULL;
}

void	decode_msg(t_list *lst, int len)
{
	int		i;
	int		j;
	uint	binary_char[8];
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
			binary_char[j] = *((uint *)(ptrlst->content));
			j++;
			ptrlst = ptrlst->next;
		}
		msg[i] = binary2char(binary_char);
		i++;
	}
	msg[i] = 0;
	printf("\nPrinting message received:\n%s\n", msg);
	printf("------ END ---- OF ---- MSG -------\n");
	free (msg);
}
