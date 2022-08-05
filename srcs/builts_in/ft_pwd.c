/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:51 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 11:05:47 by anguinau         ###   ########.fr       */
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
	getcwd(buff, size);
	while (!buff[0])
	{
		free(buff);
		size++;
		buff = malloc(sizeof(char) * size);
		if (!buff)
			return (-1);
		getcwd(buff, size);
	}
	ft_putstr_fd(buff, fd);
	free(buff);
	return (0);
}
