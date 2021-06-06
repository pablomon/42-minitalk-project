/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:41:58 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:53:04 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed_str;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_iscontained(s1[start], set))
		start++;
	end = 0;
	if (ft_strlen(s1) > 0)
		end = ft_strlen(s1) - 1;
	while (end > start && ft_iscontained(s1[end], set))
		end--;
	trimmed_str = (char *)ft_calloc(sizeof(char), end - start + 2);
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (i + start <= end)
	{
		trimmed_str[i] = s1[start + i];
		i++;
	}
	return (trimmed_str);
}
