/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrd_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:29 by jchene            #+#    #+#             */
/*   Updated: 2022/07/15 18:59:49 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_heredoc	*init_new_hrd(void)
{
	t_heredoc	*new;

	new = (t_heredoc *)ft_calloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = NULL;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}

t_heredoc	*get_heredoc(void)
{
	t_parsing	*cursor;
	int			hrd_idx;
	t_heredoc	*heredoc;
	char		*line;

	hrd_idx = 0;
	cursor = (data())->p_start;
	while (cursor && hrd_idx < count_hrd_list() + 1)
	{
		if (cursor->flag == HRD)
			hrd_idx++;
		cursor = cursor->next;
	}
	heredoc = init_new_hrd();
	if (!heredoc)
		return (0);
	if (!ft_strmcpy(cursor->str, &(heredoc->delimiter)))
		return (NULL);
	line = readline("msh_heredoc> ");
	while (!strict_cmp(heredoc->delimiter, line))
	{
		insert_line(heredoc, line);
		line = readline("msh_heredoc> ");
	}
	return (heredoc);
}

int	init_heredocs(void)
{
	int			i;
	int			count;
	t_heredoc	*heredoc;

	(data())->old_pipe[0] = -1;
	(data())->old_pipe[1] = -1;
	(data())->new_pipe[0] = -1;
	(data())->new_pipe[1] = -1;
	(data())->child_ids = (int *)ft_calloc(sizeof(int) * nb_cmds(0));
	if (!(data())->child_ids)
		return (ifree((data())->exec_struc, 0));
	i = -1;
	count = count_list_flags(HRD);
	while (++i < count)
	{
		heredoc = get_heredoc();
		if (!heredoc)
			return (0);
		insert_hrd(heredoc);
	}
	display_all_heredocs();
	return (1);
}

//Display all heredocs
void	display_all_heredocs(void)
{
	int			i;
	int			j;
	t_heredoc	*tmp;
	t_hrd_line	*tmp2;

	i = 0;
	tmp = (data())->he_start;
	while (tmp)
	{
		fprintf(stderr, "heredoc[%d]:\n", i);
		j = 0;
		tmp2 = tmp->heredoc;
		while (tmp2)
		{
			fprintf(stderr, "line[%d]: %s\n", j, tmp2->line);
			tmp2 = tmp2->next;
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

//Count heredoc number of lines
int	count_hrd_lines(t_heredoc *heredoc)
{
	int			ret;
	t_hrd_line	*tmp;

	ret = 0;
	tmp = heredoc->heredoc;
	if (tmp)
		ret++;
	while (tmp && tmp->next)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}
