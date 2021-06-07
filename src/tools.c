#include "minitalk.h"

// void binary2char(char *b)
// {
// 	int				i = 0;
// 	unsigned char	c = 0;

// 	while (i < 8)
// 	{
// 		if (b[i] == '1')
// 			c += 0x1 << i;
// 		i++;
// 	}
// 	printf("%c\n", c);
// }

// char2binary(char c, char** dest)
// {
// 	int	i = 0;

// 	char b[8] = "";
// 	while (i < 8)
// 	{
// 		unsigned char d = 0x1 & c >> i;
// 		if (d == 0)
// 			b[i] = '0';
// 		else
// 			b[i] = '1';
// 		i++;
// 	}
// 	printf("%s\n", b);
// 	binary2char(b);
// }

// void binary2int(char *b)
// {
// 	int				i = 0;
// 	unsigned int	integer = 0;

// 	while (i < sizeof(unsigned int) * 8)
// 	{
// 		if (b[i] == '1')
// 			integer += 0x1 << i;
// 		i++;
// 	}
// 	printf("%u\n", integer);
// }

// void int2binary(unsigned int n, char *str)
// {
// 	int	i = 0;

// 	while (i < sizeof(unsigned int) * 8)
// 	{
// 		unsigned char d = 0x1 & n >> i;
// 		if (d == 0)
// 			str[i] = '0';
// 		else
// 			str[i] = '1';
// 		i++;
// 	}
// }
