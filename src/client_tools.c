#include "minitalk.h"

void	input_check(int argc, const char *argv[])
{
	const char	*ptr;

	if (argc != 3)
	{
		printf("Usage: client pid message\n");
		exit(EXIT_SUCCESS);
	}
	ptr = argv[1];
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
		{
			printf("pid must be a positive number\n");
			exit(EXIT_SUCCESS);
		}
		ptr++;
	}
}
