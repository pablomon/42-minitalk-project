/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:08:55 by lenox             #+#    #+#             */
/*   Updated: 2021/03/28 19:42:46 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**array_char(int rows, int columns)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * (rows + 1));
	if (!array)
		return (0);
	i = -1;
	while (++i < rows)
	{
		array[i] = malloc(sizeof(char) * (columns + 1));
		if (!array[i])
		{
			while (++i <= 0)
			{
				free(array[i]);
				array[i] = 0;
			}
			return (0);
		}
		array[i][columns] = '\0';
	}
	array[rows] = 0;
	return (array);
}
