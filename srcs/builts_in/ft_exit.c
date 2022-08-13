/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:47 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 16:00:07 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args && args[1])
	{
		if (args && args[0] && args[1] && args[2])
		{
			printf("bash: exit: too many arguments\n");
			return ;
		}
		exit_code = ft_atoi(args[1]);
		exit_code = exit_code % 256;
		if (exit_code < 0)
		{
			exit_code *= -1;
			exit_code = 256 - exit_code;
		}
	}
	(data())->exit_code = exit_code;
	if (ft_strcmp((data())->p_start->str, "exit"))
		data()->stop = 1;
}
