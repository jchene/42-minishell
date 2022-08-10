/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 02:38:05 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 16:57:41 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_these_cases(void)
{
	if (ft_strcmp((data())->p_start->str, "-")
		|| ft_strcmp((data())->p_start->str, "_")
		|| ft_strcmp((data())->p_start->str, "@")
		|| ft_strcmp((data())->p_start->str, "°")
		|| ft_strcmp((data())->p_start->str, "]")
		|| ft_strcmp((data())->p_start->str, "=")
		|| ft_strcmp((data())->p_start->str, "+")
		|| ft_strcmp((data())->p_start->str, "£")
		|| ft_strcmp((data())->p_start->str, "$")
		|| ft_strcmp((data())->p_start->str, "?"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((data())->p_start->str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (set_int(&(data())->exit_code, 127, 0));
	}
	return (1);
}

int	check_single_str(void)
{
	if (ft_strcmp((data())->p_start->str, " ")
		|| ft_strcmp((data())->p_start->str, "\t"))
		return (set_int(&(data())->exit_code, 0, 0));
	if (ft_strcmp((data())->p_start->str, "\'\'")
		|| ft_strcmp((data())->p_start->str, "\"\""))
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (set_int(&(data())->exit_code, 127, 0));
	}
	return (1);
}

int	check_input(void)
{
	if (!(data())->p_start)
		return (0);
	if (!(data())->p_start->next && !check_single_str())
		return (0);
	if (ft_strcmp((data())->p_start->str, ":")
		|| ft_strcmp((data())->p_start->str, "#"))
		return (set_int(&(data())->exit_code, 0, 0));
	if (!check_these_cases())
		return (0);
	return (1);
}
