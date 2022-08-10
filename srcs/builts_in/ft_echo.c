/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:42 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 00:09:05 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_echo(char **str, int fd)
{
	int	h;
	int	i;
	int	n;

	h = 0;
	n = 0;
	while (str[++h])
	{
		if (str[h][0] == '-')
		{
			i = 1;
			while (str[h][i] && str[h][i] == 'n')
				i++;
			if (!str[h][i])
				n++;
			else
				break ;
		}
		else
			break ;
	}
	while (str[h])
	{
		i = -1;
		while (str[h][++i])
			write(1, &str[h][i], fd);
		if (str[h + 1])
			write(1, " ", fd);
		h++;
	}
	if (!n)
		write(1, "\n", fd);
	return (0);
}
