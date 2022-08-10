/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:52:08 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 09:39:34 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	quote_is_d_quoted(int k, int quote, int first, int last)
{
	while (--k >= 0 && !quote)
		if ((data())->p_index->str[k] == D_QUOTE && k < first)
			quote = 1;
	if (quote)
	{
		k = (data())->j;
		while (quote != 2 && (data())->p_index->str[++k])
			if ((data())->p_index->str[k] == D_QUOTE && k > last)
				quote = 2;
		if (quote == 2)
			return (0);
	}
	return (1);
}

int	is_quoted(int k, int quote)
{
	int	first;
	int	last;

	first = 0;
	last = 0;
	while (--k >= 0 && !quote)
		if ((data())->p_index->str[k] == S_QUOTE && set_int(&first, k, 1))
			quote = 1;
	if (quote)
	{
		k = (data())->j;
		while (quote != 2 && (data())->p_index->str[++k])
			if ((data())->p_index->str[k] == S_QUOTE && set_int(&last, k, 1))
				quote = 2;
		if (quote == 2)
			return (quote_is_d_quoted((data())->j, 0, first, last));
	}
	return (0);
}
