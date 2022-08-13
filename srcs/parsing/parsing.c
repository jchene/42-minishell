/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:34:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 17:57:34 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	fill_p_struct_str(void)
{
	(data())->p_index->str = ft_strndup((data())->line,
			(data())->j - (data())->i, (data())->i);
	if (!(data())->p_index->str)
		return (0);
	return (1);
}

void	init_p_struct_member(t_parsing *index)
{
	index->prev = NULL;
	index->next = NULL;
	index->flag = -1;
	index->quotes = NULL;
	index->dollars = NULL;
	index->was_quoted = 0;
	index->no_extend = 0;
	index->str = NULL;
}

int	new_p_struct_member(void)
{
	if (!(data())->p_start)
	{
		(data())->p_start = malloc(sizeof(t_parsing));
		if (!((data())->p_start))
			return (0);
		init_p_struct_member((data())->p_start);
		(data())->p_index = (data())->p_start;
	}
	else
	{
		(data())->p_index = (data())->p_start;
		while ((data())->p_index->next)
			(data())->p_index = (data())->p_index->next;
		(data())->p_index->next = malloc(sizeof(t_parsing));
		if (!((data())->p_index->next))
			return (0);
		init_p_struct_member((data())->p_index->next);
		(data())->p_index->next->prev = (data())->p_index;
		(data())->p_index = (data())->p_index->next;
	}
	return (1);
}

int	read_input(void)
{
	(data())->passif_mode = 0;
	(data())->line = readline("$ ");
	(data())->passif_mode = 1;
	if (!(data())->line)
	{
		ft_putstr_fd("exit\n", 1);
		(data())->stop = 1;
		(data())->exit_code = 0;
		return (0);
	}
	if ((data())->line && (data())->line[0])
	{
		add_history((data())->line);
		if (!(data())->h_start)
		{
			if (!init_history((data())->line))
				return (0);
		}
		else if (!add_in_history((data())->line))
			return (0);
	}
	return (1);
}
