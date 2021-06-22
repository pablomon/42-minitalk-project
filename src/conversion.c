#include "minitalk.h"

void	char2binary(char c, char *dest)
{
	int				i;
	unsigned char	d;

	i = 0;
	while (i < 8)
	{
		d = 0x1 & c >> i;
		if (d == 0)
			dest[i] = '0';
		else
			dest[i] = '1';
		i++;
	}
}

void	int2binary(uint n, char *str)
{
	int				i;
	unsigned char	d;

	i = 0;
	while (i < sizeof(uint) * 8)
	{
		d = 0x1 & n >> i;
		if (d == 0)
			str[i] = '0';
		else
			str[i] = '1';
		i++;
	}
}

char	binary2char(uint *b)
{
	int				i;
	unsigned char	c;

	i = 0;
	c = 0;
	while (i < 8)
	{
		if (b[i] == 1)
			c += 0x1 << i;
		i++;
	}
	return (c);
}

int	binary2int(uint *b)
{
	int		i;
	uint	integer;

	i = 0;
	integer = 0;
	while (i < sizeof(uint) * 8)
	{
		if (b[i] == 1)
			integer += 0x1 << i;
		i++;
	}
	return (integer);
}
