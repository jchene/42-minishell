/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:47 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 19:11:50 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_str_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_ischarset("0123456789", str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	int	e_c;

	printf("exit\n");
	if (set_int(&e_c, 0, 1) && args && args[1])
	{
		if (!is_str_num(args[1]) && set_int(&e_c, 2, 1))
			ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		else if (args && args[0] && args[1] && args[2]
			&& set_int(&(data()->exit_code), 1, 1))
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return ;
		}
		if (is_str_num(args[1]) && set_int(&e_c, ft_atoi(args[1]), 1))
		{
			e_c = e_c % 256;
			if (e_c < 0)
				e_c = 256 - (e_c * -1);
		}
	}
	(data())->exit_code = e_c;
	if (ft_strcmp((data())->p_start->str, "exit"))
		data()->stop = 1;
}
