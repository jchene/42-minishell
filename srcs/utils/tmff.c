/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:20:13 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 18:22:42 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	new_quotes(int quote)
{
	t_quotes	*index;

	index = (data())->p_index->quotes;
	while (index->next)
		index = index->next;
	index->next = malloc(sizeof(t_quotes));
	if (!index->next)
		return (0);
	index->next->quote = quote;
	index->next->quoted_from = (data())->i;
	index->next->quoted_to = (data())->j - 3;
	index->next->next = NULL;
	return (1);
}

int	was_quoted(t_quotes *index, int i)
{
	while (index)
	{
		if (i >= index->quoted_from && i <= index->quoted_to)
			return (index->quote);
		index = index->next;
	}
	return (0);
}
