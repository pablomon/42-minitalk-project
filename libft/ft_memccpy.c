/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:27:12 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 20:04:39 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dst;

	ptr_src = src;
	ptr_dst = dst;
	while (n > 0)
	{
		*ptr_dst = *ptr_src;
		if ((unsigned char)c == (unsigned char)*ptr_src)
			return ((void *)ptr_dst + 1);
		ptr_src++;
		ptr_dst++;
		n--;
	}
	return (0);
}
