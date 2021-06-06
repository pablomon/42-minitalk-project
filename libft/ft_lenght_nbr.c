/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenght_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:24:07 by lenox             #+#    #+#             */
/*   Updated: 2021/03/28 19:58:35 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	lenght_nbr(int nb)
{
	int	size_nb;
	int	result;

	result = 1;
	size_nb = 0;
	while (result)
	{
		result = nb / 10;
		nb = result;
		size_nb++;
	}
	return (size_nb);
}
