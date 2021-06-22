#define _XOPEN_SOURCE 700
#define INT_BITS sizeof(unsigned int) * 8

#include "../libft/libft.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

typedef unsigned int uint;

void	char2binary(char c, char *dest);
void	int2binary(uint n, char *str);
char	binary2char(uint *b);
int		binary2int(uint *b);

void	null_list(t_list *lst);
void	decode_msg(t_list *lst, int len);
