/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_dollars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:44:23 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 18:22:50 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	from_dollar(t_dollars *index, int i)
{
	while (index)
	{
		if (i >= index->from && i <= index->to)
			return (1);
		index = index->next;
	}
	return (0);
}

int	go_til_end(int from_hrd)
{
	(data())->i = -1;
	(data())->j = -1;
	while ((data())->p_index->str[++(data())->i])
		if ((data())->p_index->str[(data())->i] == '$'
			&& !(data())->p_index->no_extend
			&& set_int(&(data())->j, (data())->i, 1) && (from_hrd
				|| (!from_hrd && was_quoted((data())->p_index->quotes,
						(data())->i) != S_QUOTE)))
			if (!dollar_finded(1))
				return (0);
	(data())->i = 0;
	while ((data())->p_index->str[(data())->i])
		(data())->i++;
	if (!from_hrd && !split_ret())
		return (0);
	return (1);
}

void	prev_exist(t_parsing **temp)
{
	if ((data())->p_index->next)
	{
		(data())->p_index->prev->next = (data())->p_index->next;
		(data())->p_index->next->prev = (data())->p_index->prev;
	}
	else
		(data())->p_index->prev->next = NULL;
	*temp = (data())->p_index->prev;
}

int	remove_empty_member(int from_hrd, t_parsing *temp)
{
	if (!from_hrd && (data())->p_index
		&& !(data())->p_index->str[0] && !(data())->p_index->was_quoted)
	{
		if ((data())->p_index->prev)
			prev_exist(&temp);
		else if ((data())->p_index->next)
		{
			(data())->p_index->next->prev = NULL;
			(data())->p_start = (data())->p_index->next;
			(data())->p_index->next = NULL;
			(data())->p_index->prev = NULL;
			free_p_struct(&(data())->p_index);
			(data())->p_index = temp;
			return (1);
		}
		else
			(data())->p_start = NULL;
		(data())->p_index->next = NULL;
		(data())->p_index->prev = NULL;
		free_p_struct(&(data())->p_index);
		(data())->p_index = temp;
	}
	if ((data())->p_index)
		(data())->p_index = (data())->p_index->next;
	return (1);
}

int	rm_dollars(t_parsing *start, t_parsing *temp, int from_hrd)
{
	(data())->p_index = start;
	while ((data())->p_index)
	{
		if (from_hrd)
		{
			while (temp && temp->flag != HDL)
				temp = temp->next;
			if (temp && temp->flag == HDL && temp->was_quoted)
			{
				temp = temp->next;
				(data())->p_index = (data())->p_index->next;
				continue ;
			}
			temp = temp->next;
		}
		if (!go_til_end(from_hrd))
			return (0);
		remove_empty_member(from_hrd, temp);
	}
	return (1);
}
