/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:51 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/11 15:49:40 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_pwd(int fd)
{
	char	*buff;
	int		size;

	size = 1;
	buff = malloc(sizeof(char) * size);
	if (!buff)
		return (-1);
	while (!getcwd(buff, size))
	{
		free(buff);
		size++;
		buff = malloc(sizeof(char) * size);
		if (!buff)
			return (-1);
	}
	ft_putstr_fd(buff, fd);
	ft_putstr_fd("\n", fd);
	free(buff);
	return (0);
}
