/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:46:14 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 09:55:38 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_exec(void)
{
	if (((data())->exec_struc->input != (data())->old_pipe[P_RD]
			&& !fd_update(&(data())->exec_struc->input, -1))
		|| ((data())->exec_struc->output != (data())->new_pipe[P_WR]
			&& !fd_update(&(data())->exec_struc->output, -1))
		|| (!fd_update(&(data())->exec_struc->to_close[P_WR], -1)))
	{
		if ((data())->exec_struc->args)
			free_ptabn((void **)(data())->exec_struc->args);
		free((data())->exec_struc);
		(data())->exec_struc = NULL;
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
		free_exec();
	if ((data())->new_pipe[P_RD] == (data())->old_pipe[P_RD])
	{
		(data())->new_pipe[P_RD] = -1;
		if (!fd_update(&(data())->old_pipe[P_RD], -1))
			return (0);
	}
	if ((data())->new_pipe[P_WR] == (data())->old_pipe[P_WR])
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
