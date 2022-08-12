/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:45:44 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 00:08:10 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd"))
		return (1);
	if (ft_strcmp(str, "env"))
		return (2);
	if (ft_strcmp(str, "echo"))
		return (3);
	if (ft_strcmp(str, "exit"))
		return (4);
	if (ft_strcmp(str, "export"))
		return (5);
	if (ft_strcmp(str, "pwd"))
		return (6);
	if (ft_strcmp(str, "unset"))
		return (7);
	return (0);
}

int	next_cmd_is_valid(t_parsing *start)
{
	t_parsing	*temp;

	temp = start;
	if (!temp)
		return (1);
	if (temp->flag == PIP)
		temp = temp->next;
	while (temp && temp->flag != CMD)
		temp = temp->next;
	if (!temp)
		return (1);
	if (is_directory(temp->str))
		return (0);
	if (ft_ischarset(temp->str, '/'))
	{
		if (!access(temp->str, X_OK))
			return (1);
		if (!access(temp->str, F_OK))
			return (0);
	}
	if (is_builtin(temp->str))
		return (1);
	return (0);
}

int	exec_builtin(t_exec *struc)
{
	if (next_cmd_is_valid((data())->p_index))
	{
		if (ft_strcmp(struc->path, "env"))
			(data())->exit_code = ft_env(1);
		if (ft_strcmp(struc->path, "echo"))
			(data())->exit_code = ft_echo(struc->args, 1);
		if (ft_strcmp(struc->path, "export"))
			(data())->exit_code = ft_export(struc->args, 1);
		if (ft_strcmp(struc->path, "pwd"))
			(data())->exit_code = ft_pwd(1);
	}
	if (!fd_update(&struc->input, -1))
		return (0);
	if (!fd_update(&struc->output, -1))
		return (0);
	(data())->old_pipe[P_RD] = -1;
	(data())->old_pipe[P_WR] = -1;
	(data())->new_pipe[P_RD] = -1;
	(data())->new_pipe[P_WR] = -1;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit_exec((data())->exit_code);
	exit(exit_properly((data())->exit_code));
	return (0);
}

void	apply_builtin(t_exec *struc, int ret, int is_last)
{
	if (!(data())->p_index)
		is_last++;
	if ((data())->p_index && (data())->p_index->flag == PIP)
		return ;
	if (ret == 1)
	{
		ret = ft_cd(struc->args, NULL);
		if (ret != -1 && is_last && ++(data())->got_from_builtsin)
			set_int(&(data())->exit_code, ret, 0);
	}
	else if (ret == 4)
		ft_exit();
	else if (ret == 5 && struc->args[1])
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
