/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:23:32 by jchene            #+#    #+#             */
/*   Updated: 2022/08/05 06:13:03 by anguinau         ###   ########.fr       */
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
int	fill_infile(t_parsing *cursor, t_exec *struc)
{
	int	redir;

	if (access(cursor->next->str, R_OK))
	{
		(data())->skip_exec = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cursor->next->str, 2);
		return (iperror("", 1));
	}
	redir = open(cursor->next->str, O_RDONLY);
	if (redir < 0)
	{
		(data())->skip_exec = 1;
		return (iperror("minishell: infile open", 1));
	}
	if (struc->input == (data())->old_pipe[P_RD])
	{
		(data())->old_pipe[P_RD] = -1;
		(data())->old_pipe[P_WR] = -1;
	}
	if (!fd_update(&struc->input, redir)
		|| !fd_update(&struc->to_close[P_WR], -1))
		return (0);
	return (1);
}

//Get a heredoc fd and put it in infiles
int	fill_heredoc(t_exec *struc, t_parsing *htmp, int i)
{
	if (!fd_update(&(data())->he_pipe[P_RD], -1)
		|| !fd_update(&(data())->he_pipe[P_WR], -1))
		return (0);
	if (pipe((data())->he_pipe) < 0)
		return (iperror("minishell: pipe failed", 0));
	htmp = (data())->he_start;
	while (++i < (data())->he_read)
		htmp = htmp->next;
	(data())->he_read++;
	if (!ft_putstrn_fd(htmp->str, (data())->he_pipe[P_WR]))
		return (0);
	if (struc->input == (data())->old_pipe[P_RD])
	{
		(data())->old_pipe[P_RD] = -1;
		(data())->old_pipe[P_WR] = -1;
	}
	if (!fd_update(&(struc->to_close[P_WR]), (data())->he_pipe[P_WR])
		|| !fd_update(&(struc->input), (data())->he_pipe[P_RD]))
		return (0);
	(data())->he_pipe[P_WR] = -1;
	(data())->he_pipe[P_RD] = -1;
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
			if (!fill_infile(tmp, struc))
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
