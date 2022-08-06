/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:42 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 03:56:21 by anguinau         ###   ########.fr       */
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
		if (h == 1 && ft_strcmp(str[h], "-n") && ++n)
			continue ;
		i = -1;
		while (str[h][++i])
			write(1, &str[h][i], fd);
		if (str[h + 1])
			write(1, " ", fd);
	}
	if (!n)
		write(1, "\n", fd);
	return (0);
}
