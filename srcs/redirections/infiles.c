/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:23:32 by jchene            #+#    #+#             */
/*   Updated: 2022/07/29 15:03:15 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//If pipe block starts by pipe, fill it's fds into struc
void	*fill_inpipe(t_exec *struc)
{
	if (!fd_update(&struc->input, (data())->old_pipe[P_RD]))
		return (NULL);
	if (!fd_update(&struc->to_close[0], (data())->old_pipe[P_WR]))
		return (NULL);
	//fprintf(stderr, "%sFilled input-close with fd %d-%d%s\n", YELLOW_CODE, struc->input, struc->to_close[0], RESET_CODE);
	return (struc);
}

//Opens an infile and put it's fd into infiles
int	fill_infile(t_parsing *cursor, t_exec *struc)
{
	int	redir;

	if (access(cursor->next->str, R_OK))
	{
		(data())->skip_exec = 1;
		return (iperror("minishell: infile", 1));
	}
	redir = open(cursor->next->str, O_RDONLY);
	if (redir < 0)
	{
		(data())->skip_exec = 1;
		return (iperror("minishell: infile open", 1));
	}
	//fprintf(stderr, "%sOpened %s on fd %d%s\n", YELLOW_CODE, cursor->next->str, redir, RESET_CODE);
	if (!fd_update(&struc->input, redir))
		return (0);
	return (1);
}

//Get a heredoc fd and put it in infiles
int	fill_heredoc(t_exec *struc)
{
	t_heredoc	*htmp;
	t_hrd_line	*ltmp;
	int			i;
	int			out;

	(void)struc;
	if ((data())->he_pipe[P_RD] >= 0)
		close((data())->he_pipe[P_RD]);
	if ((data())->he_pipe[P_WR] >= 0)
		close((data())->he_pipe[P_WR]);
	if (pipe((data())->he_pipe) < 0)
		return (iperror("minishell: pipe failed", 0));
	htmp = (data())->he_start;
	i = -1;
	while (++i < (data())->he_read)
		htmp = htmp->next;
	ltmp = htmp->heredoc;
	while (ltmp)
	{
		write((data())->he_pipe[P_WR]);
		ltmp = ltmp->next;
	}
	return (1);
}

//Return a sorted tab of all infile fds in the pipe bock
void	*get_infiles(t_parsing *cursor, t_exec *struc)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (tmp && tmp->flag == PIP)
	{
		if (!fill_inpipe(struc))
			return (NULL);
		tmp = tmp->next;
	}
	while (tmp && tmp->flag != PIP && !(data())->skip_exec)
	{
		if (tmp->flag == INF)
			if (!fill_infile(tmp, struc))
				return (NULL);
		if (tmp->flag == HRD)
			if (!fill_heredoc(struc))
				return (NULL);
		if ((data())->skip_exec)
			return (struc);
		tmp = tmp->next;
	}
	return (struc);
}
