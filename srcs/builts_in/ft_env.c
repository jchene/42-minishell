/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:44 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 02:54:37 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_env(int fd)
{
	int	i;

	i = -1;
	while ((data())->envp && (data())->envp[++i])
	{
		if ((data())->envp[i][0] != '_' ||
			((data())->envp[i][0] == '_' && (data())->envp[i][1] == '='))
		{
			ft_putstr_fd((data())->envp[i], fd);
			ft_putstr_fd("\n", fd);
		}
	}
	return (0);
}
