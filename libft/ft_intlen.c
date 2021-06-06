/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:30:55 by pmontese          #+#    #+#             */
/*   Updated: 2019/11/26 15:30:56 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(long int nbr)
{
	int				len;
	unsigned int	unbr;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		unbr = -nbr;
		len++;
	}
	else
		unbr = nbr;
	while (unbr != 0)
	{
		unbr = unbr / 10;
		len++;
	}
	return (len);
}
