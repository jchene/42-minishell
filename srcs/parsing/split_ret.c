/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:43:15 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 17:58:59 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	detach_next(t_parsing *new, int i)
{
	while ((data())->p_index->str[i]
		&& ((data())->p_index->str[i] == ' '
			|| (data())->p_index->str[i] == '\t'))
			i++;
	if (!(data())->p_index->str[i])
		return (1);
	new = malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	new->next = (data())->p_index->next;
	if (new->next)
		(data())->p_index->next->prev = new;
	new->prev = (data())->p_index;
	(data())->p_index->next = new;
	new->dollars = NULL;
	new->no_extend = (data())->p_index->no_extend;
	new->was_quoted = (data())->p_index->was_quoted;
	new->quotes = (data())->p_index->quotes;
	new->flag = (data())->p_index->flag;
	new->str = ft_strndup((data())->p_index->str,
			ft_strlen((data())->p_index->str), i);
	if (!new->str)
		return (ifree(new, 0));
	return (1);
}

int	remove_behind(char *temp)
{
	if (!detach_next(NULL, (data())->i))
		return (0);
	temp = ft_strndup((data())->p_index->str, (data())->i, 0);
	if (!temp)
		return (0);
	free((data())->p_index->str);
	(data())->p_index->str = ft_strdup(temp);
	free(temp);
	if (!(data())->p_index->str)
		return (0);
	return (1);
}

int	split_ret(void)
{
	while (--(data())->i >= 0)
	{
		if (((data())->p_index->str[(data())->i] == ' '
				|| (data())->p_index->str[(data())->i] == '\t')
			&& !was_quoted((data())->p_index->quotes, (data())->i))
		{
			if (from_dollar((data())->p_index->dollars, (data())->i))
				(data())->p_index->no_extend++;
			while ((data())->i >= 0
				&& ((data())->p_index->str[(data())->i] == ' '
					|| (data())->p_index->str[(data())->i] == '\t')
				&& !was_quoted((data())->p_index->quotes,
					(data())->i))
				(data())->i--;
			(data())->i++;
			if (!remove_behind(NULL))
				return (0);
		}
	}
	return (1);
}
