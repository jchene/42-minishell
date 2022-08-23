/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:51:05 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 19:51:28 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_exec_struct(void)
{
	if ((data())->exec_struc->output != (data())->new_pipe[P_WR])
		if (!fd_update(&(data())->exec_struc->output, -1))
			return (0);
	if ((data())->exec_struc->input != (data())->old_pipe[P_RD])
	{
		if ((data())->exec_struc->input == (data())->he_pipe[P_RD])
			(data())->he_pipe[P_RD] = -1;
		if (!fd_update(&(data())->exec_struc->input, -1))
			return (0);
	}
	if ((data())->exec_struc->args)
		free_ptabn((void **)(data())->exec_struc->args);
	free((data())->exec_struc);
	(data())->exec_struc = NULL;
	return (1);
}

int	exit_exec(int ret)
{
	if ((data())->exec_struc)
		if (!free_exec_struct())
			return (0);
	if ((data())->new_pipe[P_RD] == (data())->old_pipe[P_RD])
	{
		(data())->new_pipe[P_RD] = -1;
		if (!fd_update(&(data())->old_pipe[P_RD], -1))
			return (0);
	}
	if ((data())->new_pipe[P_WR] == (data())->old_pipe[P_WR])
	{
		(data())->new_pipe[P_WR] = -1;
		if (!fd_update(&(data())->old_pipe[P_WR], -1))
			return (0);
	}
	if (!fd_update(&(data())->new_pipe[P_RD], -1))
		return (0);
	if (!fd_update(&(data())->new_pipe[P_WR], -1))
		return (0);
	if (!fd_update(&(data())->he_pipe[P_RD], -1))
		return (0);
	if (!fd_update(&(data())->he_pipe[P_WR], -1))
		return (0);
	return (ret);
}

//Allocate exec struc tab, exec strucs and child id tab
int	init_exec(void)
{
	if ((data())->exec_struc)
		if (!free_exec_struct())
			return (0);
	(data())->exec_struc = (t_exec *)ft_calloc(sizeof(t_exec));
	if (!(data())->exec_struc)
		return (0);
	if ((data())->skip_exec)
		(data())->last_skip = 1;
	else
		(data())->last_skip = 0;
	(data())->skip_exec = 0;
	(data())->exec_struc->input = -1;
	(data())->exec_struc->output = -1;
	(data())->exec_struc->to_close[P_RD] = -1;
	(data())->exec_struc->to_close[P_WR] = -1;
	(data())->exec_struc->out_pipe[P_RD] = -1;
	(data())->exec_struc->out_pipe[P_WR] = -1;
	(data())->exec_struc->path = NULL;
	(data())->exec_struc->args = NULL;
	(data())->he_pipe[P_RD] = -1;
	(data())->he_pipe[P_WR] = -1;
	return (1);
}

int	first_init(void)
{
	(data())->exec_struc = NULL;
	(data())->old_pipe[P_RD] = -1;
	(data())->old_pipe[P_WR] = -1;
	(data())->new_pipe[P_RD] = -1;
	(data())->new_pipe[P_WR] = -1;
	(data())->skip_exec = 0;
	(data())->last_skip = 0;
	(data())->child_ids = (int *)ft_calloc(sizeof(pid_t) * nb_pipes(NO_UP));
	if (!(data())->child_ids)
		return (0);
	return (1);
}

//Wait for all childs to terminate
int	wait_all(void)
{
	int	i;
	int	temp;
	int	success;

	i = -1;
	temp = -1;
	success = 0;
	while (++i < nb_pipes(NO_UP))
	{
		if ((data())->child_ids[i] != -1)
			if (waitpid((data())->child_ids[i], &temp, 0) < 0)
				return (iperror("minishell: waitpid", 0));
		if (!(data())->got_from_builtsin && !(data())->skip_exec
			&& !success && temp && temp != 2 && temp != 131)
			(data())->exit_code = WEXITSTATUS(temp);
		if (!(data())->got_from_builtsin && !(data())->skip_exec
			&& !temp && ++success)
			(data())->exit_code = 0;
	}
	return (1);
}
