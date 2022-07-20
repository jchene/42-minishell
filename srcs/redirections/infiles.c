/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:23:32 by jchene            #+#    #+#             */
/*   Updated: 2022/07/20 17:16:09 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//If pipe block starts by pipe, fill it's fds into struc
void	*fill_inpipe(t_parsing **cursor, t_exec *struc)
{
	if (!fd_update(&struc->input, (data())->old_pipe[P_RD]))
		return (NULL);
	fprintf(stderr, "%sFilled input with fd %d%s\n", YELLOW_CODE, struc->input, RESET_CODE);
	/*if ((close((data())->old_pipe[P_WR]) < 0))
		return (pperror("minishell: close"));
	fprintf(stderr, "%sClosing other end fd %d%s\n", YELLOW_CODE, data())->old_pipe[P_WR], RESET_CODE);*/
	(*cursor) = (*cursor)->next;
	return (struc);
}

//Opens an infile and put it's fd into infiles
int	fill_infile(t_parsing *cursor, t_exec *struc, int *error)
{
	int	redir;

	if (access(cursor->next->str, R_OK))
	{
		*error = 1;
		return (iperror("minishell: infile:", 1));
	}
	redir = open(cursor->next->str, O_RDONLY);
	if (redir < 0)
	{
		*error = 1;
		return (iperror("minishell: open:", 1));
	}
	fprintf(stderr, "%sOpened %s on fd %d%s\n", YELLOW_CODE, cursor->next->str, redir, RESET_CODE);
	if (!fd_update(&struc->input, redir))
		return (0);
	return (1);
}

//Get a heredoc fd and put it in infiles
int	fill_heredoc(t_parsing *cursor, t_exec *struc)
{
	(void)cursor;
	(void)struc;
	return (1);
}

//Return a sorted tab of all infile fds in the pipe bock
void	*get_infiles(t_parsing *cursor, t_exec *struc)
{
	t_parsing	*tmp;
	int			error;

	tmp = cursor;
	error = 0;
	if (tmp && tmp->flag == PIP)
		if (!fill_inpipe(&tmp, struc))
			return (NULL);
	while (tmp && tmp->flag != PIP)
	{
		if (tmp->flag == INF)
			if (!fill_infile(tmp, struc, &error))
				return (NULL);
		if (error)
			return (struc);
		tmp = tmp->next;
	}
	return (struc);
}
