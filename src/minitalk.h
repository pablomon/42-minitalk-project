#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define INT_BITS sizeof(unsigned int) * 8

typedef unsigned int uint;
typedef struct		s_list
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
void	int2binary(uint n, char *str);
char	binary2char(uint *b);
int		binary2int(uint *b);

void	print_chars(uint bitval);
void	null_list(t_list *lst);
void	decode_msg(t_list *lst, int len, pid_t pid);

void	input_check(int argc, const char *argv[]);
