/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:23:32 by jchene            #+#    #+#             */
/*   Updated: 2022/07/15 19:07:39 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//If pipe block starts by pipe, fill it's fds into struc
void	fill_inpipe(t_parsing **cursor, t_exec *struc)
{
	struc->infiles[(data())->nb_inf] = (data())->old_pipe[P_RD];
	(data())->nb_inf++;
	struc->to_close[(data())->nb_cls] = (data())->old_pipe[P_WR];
	(data())->nb_cls++;
	*cursor = (*cursor)->next;
}

//Opens an infile and put it's fd into infiles
int	fill_infile(t_parsing *cursor, t_exec *struc)
{
	struc->infiles[(data())->nb_inf] = open(cursor->next->str, O_RDONLY);
	if (struc->infiles[(data())->nb_inf] < 0)
		return (iperror("Minishell: open", 1));
	fprintf(stderr, "%sOpening '%s' on fd '%d'%s\n", YELLOW_CODE, cursor->next->str, struc->infiles[(data())->nb_inf], RESET_CODE);
	(data())->nb_inf++;
	return (1);
}

//Get a heredoc fd and put it in infiles
int	fill_heredoc(t_parsing *cursor, t_exec *struc)
{
	(void)cursor;
	(void)struc;
	return (1);
}

//Fill tab infiles with fds of infiles of the pipe block
void	*fill_with_infiles(t_parsing *cursor, t_exec *struc)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (!tmp)
		return (struc);
	(data())->nb_cls = 0;
	if (tmp->flag == PIP)
		fill_inpipe(&tmp, struc);
	while (tmp && tmp->flag != PIP)
	{
		if (tmp->flag == INF || tmp->flag == HRD)
		{
			if (tmp->flag == INF)
				if (!fill_infile(tmp, struc))
					return (NULL);
			if (tmp->flag == HRD)
				if (!fill_heredoc(tmp, struc))
					return (NULL);
		}
		tmp = tmp->next;
	}
	return (struc);
}

//Return a sorted tab of all infile fds in the pipe bock
void	*get_infiles(t_parsing *cursor, t_exec *struc)
{
	int			total_inf;

	total_inf = itern((cursor->flag == PIP), 1, 0);
	total_inf += count_block_flags(cursor, INF);
	//total_inf += count_block_flags(cursor, HRD);
	(data())->nb_inf = 0;
	struc->infiles = (int *)ft_calloc(sizeof(int) * total_inf);
	if (!struc->infiles)
		return (NULL);
	if (!fill_with_infiles(cursor, struc))
	{
		free(struc->infiles);
		return (NULL);
	}
	return (struc);
}
