/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:01:53 by jchene            #+#    #+#             */
/*   Updated: 2022/07/20 17:11:21 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Returns number of commands in pipeline. Use flags UP or NO_UP to update or not
int	nb_cmds(int flag)
{
	static int	ret = -1;
	t_parsing	*tmp;

	if (flag)
		ret = -1;
	if (ret == -1)
	{
		tmp = (data())->p_start;
		ret = 0;
		while (tmp)
		{
			if (tmp->flag == CMD)
				ret++;
			tmp = tmp->next;
		}
	}
	return (ret);
}

//Wait for all childs to terminate
void	wait_all(void)
{
	int	i;

	i = -1;
	fprintf(stderr, "%sWaiting for all%s\n", YELLOW_CODE, RESET_CODE);
	while (++i < nb_cmds(NO_UP))
	{
		fprintf(stderr, "%sWaiting for [%d]: %d%s\n", YELLOW_CODE, i, (data())->child_ids[i], RESET_CODE);
		waitpid((data())->child_ids[i], NULL, 0);
		fprintf(stderr, "%sChild[%d] done%s\n", YELLOW_CODE, (data())->child_ids[i], RESET_CODE);
	}
	fprintf(stderr, "%sAll childs done.%s\n", YELLOW_CODE, RESET_CODE);
}

//Returns 1 if a pipe is present at then end of block cursor, 0 otherwise
int	pipe_at_end(t_parsing *cursor)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	while (tmp && tmp->flag != PIP)
		tmp = tmp->next;
	if (tmp && tmp->flag == PIP)
		return (1);
	return (0);
}

int	fd_update(int *fd_ptr, int value)
{
	if (*fd_ptr >= 0)
		if (close(*fd_ptr) < 0)
			return (iperror("minishell: close", 0));
	*fd_ptr = value;
	return (1);
}
