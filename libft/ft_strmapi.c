/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:39:15 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 20:05:13 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*modstr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	modstr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!modstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		modstr[i] = f(i, s[i]);
		i++;
	}
	modstr[i] = '\0';
	return (modstr);
}
