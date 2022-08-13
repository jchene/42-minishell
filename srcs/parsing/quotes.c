/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:01:06 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 18:22:08 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	first_quotes(int quote)
{
	(data())->p_index->quotes = malloc(sizeof(t_quotes));
	if (!(data())->p_index->quotes)
		return (0);
	(data())->p_index->quotes->quote = quote;
	(data())->p_index->quotes->quoted_from = (data())->i;
	(data())->p_index->quotes->quoted_to = (data())->j - 3;
	(data())->p_index->quotes->next = NULL;
	return (1);
}

int	mark_dollar(t_quotes *index, int quote)
{
	if (!(data())->p_index->quotes)
	{
		(data())->p_index->quotes = malloc(sizeof(t_quotes));
		if (!(data())->p_index->quotes)
			return (0);
		(data())->p_index->quotes->quote = quote;
		(data())->p_index->quotes->quoted_from = (data())->i - 1;
		(data())->p_index->quotes->quoted_to = (data())->i - 1;
		(data())->p_index->quotes->next = NULL;
		return (1);
	}
	else
	{
		index = (data())->p_index->quotes;
		while (index->next)
			index = index->next;
		index->next = malloc(sizeof(t_quotes));
		if (!index->next)
			return (0);
		index->next->quote = quote;
		index->next->quoted_from = (data())->i - 1;
		index->next->quoted_to = (data())->i - 1;
		index->next->next = NULL;
	}
	return (1);
}

int	remove_quotes(int quote, char *old, char *buff, int ret)
{
	ret = replace_it(1, &old, &buff);
	if (old)
		free(old);
	if (buff)
		free(buff);
	if ((data())->temp)
		free((data())->temp);
	if ((data())->i > 0 && (data())->p_index->str[(data())->i - 1] == '$')
		if (!mark_dollar(NULL, quote))
			return (0);
	if ((data())->j - 3 > (data())->i && !(data())->p_index->quotes)
	{
		if (!first_quotes(quote))
			return (0);
	}
	else if ((data())->j - 3 > (data())->i && !new_quotes(quote))
		return (0);
	(data())->p_index->was_quoted++;
	(data())->i += (data())->offset - 1;
	(data())->temp = NULL;
	return (ret);
}

int	quote_finded(int quote, int ret)
{
	(data())->j = (data())->i + 1;
	while ((data())->p_index->str[(data())->j])
	{
		if ((data())->p_index->str[(data())->j] == quote)
		{
			(data())->temp = ft_strndup((data())->p_index->str,
					(data())->j - (data())->i - 1, (data())->i + 1);
			if (!(data())->temp)
				return (0);
			(data())->j++;
			ret = remove_quotes(quote, NULL, NULL, 0);
			if (!ret)
				return (ret);
			break ;
		}
		else
			(data())->j++;
	}
	return (ret);
}

int	rm_quotes(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		(data())->i = -1;
		(data())->j = -1;
		while ((data())->p_index->str[++(data())->i])
		{	
			if ((data())->i > (data())->j - 3
				&& ((data())->p_index->str[(data())->i] == S_QUOTE
					|| (data())->p_index->str[(data())->i] == D_QUOTE))
				if (!quote_finded((data())->p_index->str[(data())->i], 1))
					return (0);
		}
		(data())->p_index = (data())->p_index->next;
	}
	return (1);
}
