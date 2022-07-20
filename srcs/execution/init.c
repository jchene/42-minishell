/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:51:05 by jchene            #+#    #+#             */
/*   Updated: 2022/07/20 17:10:26 by jchene           ###   ########.fr       */
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
	(data())->skip_exec = 0;
	(data())->exec_struc->to_close[0] = -1;
	(data())->exec_struc->to_close[1] = -1;
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
	if ((data())->child_ids)
	{
		free((data())->child_ids);
		(data())->child_ids = NULL;
	}
	return (ret);
}
