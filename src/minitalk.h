/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:21:56 by pmontese          #+#    #+#             */
/*   Updated: 2021/07/15 18:29:51 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

typedef unsigned int	t_uint;
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstnew(void const *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);

void	char2binary(char c, char *dest);
void	int2binary(t_uint n, char *str);
char	binary2char(t_uint *b);
int		binary2int(t_uint *b);

void	print_chars(t_uint bitval);
void	null_list(t_list *lst);
void	decode_msg(t_list *lst, int len, pid_t pid);

void	input_check(int argc, const char *argv[]);

#endif
