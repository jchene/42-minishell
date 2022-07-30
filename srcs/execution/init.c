/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:51:05 by jchene            #+#    #+#             */
/*   Updated: 2022/07/30 17:34:32 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	first_init(void)
{
	(data())->old_pipe[0] = -1;
	(data())->old_pipe[1] = -1;
	(data())->new_pipe[0] = -1;
	(data())->new_pipe[1] = -1;
	(data())->child_ids = (int *)ft_calloc(sizeof(int) * nb_cmds(NO_UP));
	if (!(data())->child_ids)
		return (ifree((data())->exec_struc, 0));
	(data())->exec_struc = NULL;
	(data())->skip_exec = 0;
	(data())->last_skip = 0;
	return (1);
}

//Allocate exec struc tab, exec strucs and child id tab
int	init_exec(void)
{
	if ((data())->exec_struc)
	{
		free((data())->exec_struc->path);
		free_ptabn((void **)(data())->exec_struc->args);
		free((data())->exec_struc);
		(data())->exec_struc = NULL;
	}
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
	(data())->he_pipe[P_RD] = -1;
	(data())->he_pipe[P_WR] = -1;
	return (1);
}

int	free_exec(int ret)
{
	if ((data())->exec_struc)
	{
		free((data())->exec_struc->path);
		free_ptabn((void **)(data())->exec_struc->args);
		free((data())->exec_struc);
		(data())->exec_struc = NULL;
	}
	if ((data())->new_pipe[P_RD] != (data())->old_pipe[P_RD])
	{
		(data())->new_pipe[P_RD] = -1;
		if (!fd_update(&(data())->old_pipe[P_RD], -1))
			return (0);
	}
	if ((data())->new_pipe[P_WR] != (data())->old_pipe[P_WR])
	{
		(data())->new_pipe[P_WR] = -1;
		if (!fd_update(&(data())->old_pipe[P_RD], -1))
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


