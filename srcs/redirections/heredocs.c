/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:29 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 19:37:21 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	add_new_line(t_parsing *index)
{
	while (index->next)
		index = index->next;
	index->next = malloc(sizeof(t_parsing));
	if (!index->next)
	{
		free((data())->line);
		(data())->line = NULL;
		return (0);
	}
	init_p_struct_member(index->next);
	index = index->next;
	index->str = ft_strdup((data())->line);
	if (!index->str)
	{
		free(index);
		free((data())->line);
		(data())->line = NULL;
		return (0);
	}
	free((data())->line);
	(data())->line = NULL;
	return (1);
}

int	init_lines(void)
{
	(data())->lines = malloc(sizeof(t_parsing));
	if (!(data())->lines)
	{
		free((data())->line);
		(data())->line = NULL;
		return (0);
	}
	init_p_struct_member((data())->lines);
	(data())->lines->str = ft_strdup((data())->line);
	if (!(data())->lines->str)
	{
		free((data())->lines);
		free((data())->line);
		(data())->line = NULL;
		return (0);
	}
	free((data())->line);
	(data())->line = NULL;
	return (1);
}

int	get_lines(char **str, int ret)
{
	*str = NULL;
	ret = get_new_line(0);
	if (!ret || ret == -1)
		return (end_of_hrd(str, ret));
	while ((data())->line
		&& !ft_strcmp((data())->p_index->next->str, (data())->line))
	{
		if (!(data())->lines)
		{
			if (!init_lines())
				return (end_of_hrd(str, 0));
			ret = get_new_line(0);
			if (!ret || ret == -1)
				return (end_of_hrd(str, ret));
			continue ;
		}
		if (!add_new_line((data())->lines))
			return (end_of_hrd(str, 0));
		ret = get_new_line(0);
		if (!ret || ret == -1)
			return (end_of_hrd(str, ret));
	}
	return (end_of_hrd(str, 1));
}

int	new_heredoc(int ret)
{
	if (!(data())->he_start)
	{
		(data())->he_start = malloc(sizeof(t_parsing));
		if (!(data())->he_start)
			return (0);
		init_p_struct_member((data())->he_start);
		ret = get_lines(&(data())->he_start->str, 0);
		if (!ret || ret == -1)
			return (ret);
	}
	else
	{
		(data())->he_index = (data())->he_start;
		while ((data())->he_index->next)
			(data())->he_index = (data())->he_index->next;
		(data())->he_index->next = malloc(sizeof(t_parsing));
		if (!(data())->he_index->next)
			return (0);
		init_p_struct_member((data())->he_start);
		ret = get_lines(&(data())->he_index->next->str, 0);
		if (!ret || ret == -1)
			return (ret);
	}
	return (1);
}

int	init_heredocs(void)
{
	int	ret;

	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		if ((data())->p_index->flag == HRD)
		{
			ret = new_heredoc(0);
			if (!ret)
				return (ret);
			if (ret == -1)
			{
				(data())->got_from_builtsin++;
				(data())->exit_code = 130;
				return (ret);
			}
		}
		(data())->p_index = (data())->p_index->next;
	}
	if ((data())->he_start && (data())->he_start->str
		&& (data())->he_start->str)
		rm_dollars((data())->he_start, (data())->p_start, 1);
	return (1);
}
