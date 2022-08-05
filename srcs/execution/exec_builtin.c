/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:45:44 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 16:53:53 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "cd", 2))
		return (1);
	if (ft_strncmp(str, "env", 3))
		return (2);
	/*if (ft_strncmp(str, "/usr/bin/env", 12))
		return (2);*/
	if (ft_strncmp(str, "echo", 4))
		return (3);
	/*if (ft_strncmp(str, "/usr/bin/echo", 13))
		return (3);*/
	if (ft_strncmp(str, "exit", 4))
		return (4);
	if (ft_strncmp(str, "export", 6))
		return (5);
	if (ft_strncmp(str, "pwd", 3))
		return (6);
	/*if (ft_strncmp(str, "/usr/bin/pwd", 12))
		return (6);*/
	if (ft_strncmp(str, "unset", 5))
		return (7);
	return (0);
}

int	exec_builtin(t_exec *struc)
{
	if (ft_strncmp(struc->path, "env", 3))
		(data())->exit_code
			= ft_env(is_equal(struc->output, -1, 1, struc->output));
	/*if (ft_strncmp(struc->path, "/usr/bin/env", 12))
		(data())->exit_code
			= ft_env(is_equal(struc->output, -1, 1, struc->output));*/
	if (ft_strncmp(struc->path, "echo", 4))
		(data())->exit_code = ft_echo(struc->args,
				is_equal(struc->output, -1, 1, struc->output));
	/*if (ft_strncmp(struc->path, "/usr/bin/echo", 13))
		(data())->exit_code = ft_echo(struc->args,
				is_equal(struc->output, -1, 1, struc->output));*/
	if (ft_strncmp(struc->path, "export", 6))
		(data())->exit_code = ft_export(struc->args,
				is_equal(struc->output, -1, 1, struc->output));
	if (ft_strncmp(struc->path, "pwd", 3))
		(data())->exit_code
			= ft_pwd(is_equal(struc->output, -1, 1, struc->output));
	/*if (ft_strncmp(struc->path, "/usr/bin/pwd", 12))
		(data())->exit_code
			= ft_pwd(is_equal(struc->output, -1, 1, struc->output));*/
	exit(exit_exec((data())->exit_code));
	return (1);
}

void	apply_builtin(t_exec *struc, int ret, int is_last)
{
	if (!(data())->p_index)
		is_last++;
	if (ret == 1)
	{
		ret = ft_cd(struc->args);
		if (ret != -1 && is_last && ++(data())->got_from_builtsin)
			set_int(&(data())->exit_code, ret, 0);
	}
	else if (ret == 4)
		ft_exit();
	else if (ret == 5)
	{
		ret = ft_export(struc->args, 0);
		if (ret != -1 && is_last && ++(data())->got_from_builtsin)
			set_int(&(data())->exit_code, ret, 0);
	}
	else if (ret == 7)
	{
		ret = ft_unset(struc->args);
		if (ret != -1 && is_last && ++(data())->got_from_builtsin)
			set_int(&(data())->exit_code, ret, 0);
	}
	if (ret == -1)
		(data())->stop = 1;
}
