/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:23:32 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 17:32:00 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//If pipe block starts by pipe, fill it's fds into struc
void	*fill_inpipe(t_exec *struc)
{
	if (!fd_update(&struc->input, (data())->old_pipe[P_RD]))
		return (NULL);
	if (!fd_update(&struc->to_close[P_WR], (data())->old_pipe[P_WR]))
		return (NULL);
	return (struc);
}

//Opens an infile and put it's fd into infiles
int	fill_infile(t_parsing *cursor, t_exec *struc, int redir)
{
	if (is_directory(cursor->next->str))
		return (display_error(ER_CMD_DI, cursor->next->str, GNRL_ERR) + 1);
	if (access(cursor->next->str, F_OK))
		return (display_error(ER_CMD_PA, cursor->next->str, GNRL_ERR) + 1);
	if (access(cursor->next->str, R_OK))
		return (display_error(ER_CMD_PE, cursor->next->str, GNRL_ERR) + 1);
	redir = open(cursor->next->str, O_RDONLY);
	if (redir < 0)
	{
		(data())->skip_exec = 1;
		return (iperror("minishell: infile open", 1));
	}
	if (struc->input == (data())->old_pipe[P_RD])
	{
		if ((data())->old_pipe[P_RD] == (data())->new_pipe[P_RD])
			(data())->new_pipe[P_RD] = -1;
		if ((data())->old_pipe[P_WR] == (data())->new_pipe[P_WR])
			(data())->new_pipe[P_WR] = -1;
		(data())->old_pipe[P_RD] = -1;
		(data())->old_pipe[P_WR] = -1;
	}
	if (!fd_update(&struc->input, redir)
		|| !fd_update(&struc->to_close[P_WR], -1))
		return (0);
	return (1);
}

int	prepare_hdr(t_exec *struc)
{
	if (!fd_update(&(data())->he_pipe[P_RD], -1)
		|| !fd_update(&(data())->he_pipe[P_WR], -1))
		return (0);
	if ((data())->he_read)
	{
		struc->to_close[P_WR] = -1;
		struc->input = -1;
	}
	if (pipe((data())->he_pipe) < 0)
		return (iperror("minishell: pipe failed", 0));
	return (1);
}

//Get a heredoc fd and put it in infiles
int	fill_heredoc(t_exec *struc, t_parsing *htmp, int i)
{
	if (!prepare_hdr(struc))
		return (0);
	htmp = (data())->he_start;
	while (++i < (data())->he_read)
		htmp = htmp->next;
	(data())->he_read++;
	if (!ft_putstrn_fd(htmp->str, (data())->he_pipe[P_WR]))
		return (0);
	if (struc->input == (data())->old_pipe[P_RD])
	{
		if ((data())->old_pipe[P_RD] == (data())->new_pipe[P_RD])
			(data())->new_pipe[P_RD] = -1;
		if ((data())->old_pipe[P_WR] == (data())->new_pipe[P_WR])
			(data())->new_pipe[P_WR] = -1;
		(data())->old_pipe[P_RD] = -1;
		(data())->old_pipe[P_WR] = -1;
	}
	if (!fd_update(&(struc->to_close[P_WR]), (data())->he_pipe[P_WR])
		|| !fd_update(&(struc->input), (data())->he_pipe[P_RD]))
		return (0);
	return (1);
}

//Return a sorted tab of all infile fds in the pipe bock
void	*get_infiles(t_parsing *tmp, t_exec *struc)
{
	if (tmp && tmp->flag == PIP)
	{
		if (!fill_inpipe(struc))
			return (NULL);
		tmp = tmp->next;
	}
	while (tmp && tmp->flag != PIP && !(data())->skip_exec)
	{
		if (tmp->flag == INF)
			if (!fill_infile(tmp, struc, 0))
				return (NULL);
		if (tmp->flag == HRD)
			if (!fill_heredoc(struc, NULL, -1))
				return (NULL);
		if ((data())->skip_exec)
			return (struc);
		tmp = tmp->next;
	}
	return (struc);
}
