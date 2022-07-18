/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:51 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 18:42:03 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_pwd(void)
{
	char	*buff;
	int		size;

	size = 1;
	buff = malloc(sizeof(char) * size + 1);
	if (!buff)
		return (0);
	getcwd(buff, size);
	while (!buff[0])
	{
		free(buff);
		size++;
		buff = malloc(sizeof(char) * size + 1);
		if (!buff)
			return (0);
		getcwd(buff, size);
	}
	printf("%s\n", buff);
	free(buff);
	return (1);
}
