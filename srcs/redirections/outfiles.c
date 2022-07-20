/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:16:46 by jchene            #+#    #+#             */
/*   Updated: 2022/07/20 17:09:58 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/*void	fill_outpipe(t_exec *struc)
{
	struc->outfiles[(data())->nb_ouf] = (data())->new_pipe[P_WR];
	(data())->nb_ouf++;
	struc->to_close[(data())->nb_cls] = (data())->new_pipe[P_RD];
	(data())->nb_cls++;
}

int	fill_outfile(t_parsing *cursor, t_exec *struc, int flag)
{
	if (flag == ROF)
		struc->outfiles[(data())->nb_ouf] = open(cursor->next->str,
				O_WRONLY | O_TRUNC | O_CREAT, 00622);
	else
		struc->outfiles[(data())->nb_ouf] = open(cursor->next->str,
				O_WRONLY | O_APPEND, 00622);
	if (struc->outfiles[(data())->nb_inf] < 0)
		return (iperror("Minishell: open", 0));
	fprintf(stderr, "%sOpening '%s' on fd '%d'%s\n", YELLOW_CODE, cursor->next->str, struc->outfiles[(data())->nb_ouf], RESET_CODE);
	(data())->nb_ouf++;
	return (1);
}

//Fill tab outfiles with fds of outfiles of the pipe block
void	*fill_with_outfiles(t_parsing *cursor, t_exec *struc)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (!tmp)
		return (struc);
	if (tmp->flag == PIP)
		tmp = tmp->next;
	if (pipe_at_end(tmp))
		fill_outpipe(struc);
	while (tmp && tmp->flag != PIP)
	{
		if (tmp->flag == AOF || tmp->flag == ROF)
			if (!fill_outfile(tmp, struc, tmp->flag))
				return (NULL);
		tmp = tmp->next;
	}
	return (struc);
}

//Return a sorted tab of all outfile fds in the pipe bock
void	*get_outfiles(t_parsing *cursor, t_exec *struc)
{
	int	total_ouf;

	total_ouf = itern(pipe_at_end(cursor), 1, 0);
	total_ouf += count_block_flags(cursor, AOF);
	total_ouf += count_block_flags(cursor, ROF);
	struc->outfiles = (int *)ft_calloc(sizeof(int) * total_ouf);
	if (!struc->outfiles)
		return (NULL);
	if (!fill_with_outfiles(cursor, struc))
	{
		free(struc->outfiles);
		return (NULL);
	}
	return (struc);
}
*/