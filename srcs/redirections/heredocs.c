/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:29 by jchene            #+#    #+#             */
/*   Updated: 2022/08/04 22:15:51 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_parsing	*new_line(char *src)
{
	t_parsing	*dst;

	dst = malloc(sizeof(t_parsing));
	if (!dst)
	{
		free((data())->line);
		return (NULL);
	}
	dst->next = NULL;
	dst->str = ft_strdup(src);
	if (!dst->str)
	{
		free(dst);
		free((data())->line);
		return (NULL);
	}
	free((data())->line);
	return (dst);
}

char	*get_lines(t_parsing *lines, t_parsing *index)
{
	(data())->line = readline("> ");
	while ((data())->line && (!(data())->line[0]
			|| !ft_strncmp((data())->p_index->next->str, (data())->line,
				ft_strlen((data())->line))))
	{
		if (!lines)
		{
			lines = new_line((data())->line);
			if (!lines)
				return (NULL);
			index = lines;
			(data())->line = readline("> ");
			continue ;
		}
		index->next = new_line((data())->line);
		if (!index->next)
		{
			free_p_struct(&lines);
			return (NULL);
		}
		index = index->next;
		(data())->line = readline("> ");
	}
	return (end_of_hrd(lines));
}

int	new_heredoc(void)
{
	if (!(data())->he_start)
	{
		(data())->he_start = malloc(sizeof(t_parsing));
		if (!(data())->he_start)
			return (0);
		(data())->he_start->next = NULL;
		(data())->he_start->str = get_lines(NULL, NULL);
		if (!(data())->he_start->str)
			return (0);
	}
	else
	{
		(data())->he_index = (data())->he_start;
		while ((data())->he_index->next)
			(data())->he_index = (data())->he_index->next;
		(data())->he_index->next = malloc(sizeof(t_parsing));
		if (!(data())->he_index->next)
			return (0);
		(data())->he_index->next->next = NULL;
		(data())->he_index->next->str = get_lines(NULL, NULL);
		if (!(data())->he_index->next->str)
			return (0);
	}
	return (1);
}

int	init_heredocs(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		if ((data())->p_index->flag == HRD)
			if (!new_heredoc())
				return (0);
		(data())->p_index = (data())->p_index->next;
	}
	if ((data())->he_start)
		rm_dollars((data())->he_start, NULL, 1);
	return (1);
}
