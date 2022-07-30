/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:16:46 by jchene            #+#    #+#             */
/*   Updated: 2022/07/30 17:34:37 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	*fill_outpipe(t_exec *struc)
{
	if (!fd_update(&struc->output, (data())->new_pipe[P_WR]))
		return (NULL);
	if (!fd_update(&struc->to_close[1], (data())->new_pipe[P_RD]))
		return (NULL);
	//fprintf(stderr, "%sFilled output-close with fd %d-%d%s\n", YELLOW_CODE, struc->output, struc->to_close[1], RESET_CODE);
	return (struc);
}

int	fill_outfile(t_parsing *cursor, t_exec *struc, int flag)
{
	int	redir;

	if (flag == ROF)
		redir = open(cursor->next->str, O_WRONLY | O_TRUNC | O_CREAT, 00622);
	else
		redir = open(cursor->next->str, O_WRONLY | O_APPEND, 00622);
	if (redir < 0)
	{
		(data())->skip_exec = 1;
		return (iperror("Minishell: outfile open", 1));
	}
	//fprintf(stderr, "%sOpening '%s' on fd '%d'%s\n", YELLOW_CODE, cursor->next->str, redir, RESET_CODE);
	if (struc->output == (data())->new_pipe[P_WR])
	{
		struc->out_pipe[P_RD] = (data())->new_pipe[P_RD];
		struc->out_pipe[P_WR] = (data())->new_pipe[P_WR];
		struc->output = redir;
		struc->to_close[P_RD] = -1;
	}
	else
		if (!fd_update(&(struc->output), redir))
			return (0);
	return (1);
}

//Return a sorted tab of all outfile fds in the pipe bock
void	*get_outfiles(t_parsing *cursor, t_exec *struc)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	if (tmp && pipe_at_end(tmp))
		if (!fill_outpipe(struc))
			return (NULL);
	while (tmp && tmp->flag != PIP && !(data())->skip_exec)
	{
		if (tmp->flag == AOF || tmp->flag == ROF)
			if (!fill_outfile(tmp, struc, tmp->flag))
				return (NULL);
		tmp = tmp->next;
	}
	return (struc);
}
