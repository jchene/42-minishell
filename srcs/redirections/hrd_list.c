/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:44:19 by jchene            #+#    #+#             */
/*   Updated: 2022/07/08 16:36:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	insert_hrd(t_heredoc *heredoc)
{
	t_heredoc	*tmp;

	tmp = (data())->he_start;
	if (!tmp)
		return (set_ptr((void **)&((data())->he_start), heredoc, 1));
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = heredoc;
	return (1);
}

int	insert_line(t_heredoc *heredoc, char *line)
{
	t_hrd_line	*new_line;
	t_hrd_line	*tmp;

	new_line = (t_hrd_line *)ft_calloc(sizeof(t_hrd_line));
	if (!new_line)
		return (0);
	new_line->next = NULL;
	if (!ft_strmcpy(line, &(new_line->line)))
		return (0);
	tmp = heredoc->heredoc;
	if (!tmp)
		return (set_ptr((void **)&(heredoc->heredoc), new_line, 1));
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_line;
	return (1);
}

void	clear_heredoc(t_hrd_line *line)
{
	if (line->next)
		clear_heredoc(line->next);
	if (line->line)
		free(line->line);
	free(line);
}

void	clear_all_heredocs(t_heredoc *heredoc)
{
	if (heredoc->next)
		clear_all_heredocs(heredoc->next);
	if (heredoc->delimiter)
		free(heredoc->delimiter);
	clear_heredoc(heredoc->heredoc);
	free(heredoc);
}

//Count heredocs in heredocs list
int	count_hrd_list(void)
{
	t_heredoc	*tmp;
	int			ret;

	ret = 0;
	tmp = (data())->he_start;
	if (tmp)
		ret++;
	while (tmp && tmp->next)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}
