/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:13:02 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 03:21:10 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_intlen(int n)
{
	size_t	count;

	count = 0;
	if (!n)
		count = 1;
	while (n)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

// Malloc & return un char* qui contient le nombre N
char	*ft_itoa(int n)
{
	size_t			len;
	char			*str;
	unsigned int	n_tmp;

	n_tmp = (unsigned int)n;
	len = ft_intlen(n_tmp);
	if (n < 0)
		n_tmp = -(unsigned int)n;
	if (n < 0)
		len = ft_intlen(n_tmp) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n_tmp % 10 + '0';
		n_tmp /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
