/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:01:06 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 18:48:15 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	remove_quotes(void)
{
	char	*old;
	char	*buff;
	int		ret;

	old = NULL;
	buff = NULL;
	ret = replace_it(1, &old, &buff);
	if (old)
		free (old);
	if (buff)
		free (buff);
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
			(data())->j++;
			ret = remove_quotes();
			if (!ret)
				return (ret);
			break ;
		}
		else
			(data())->j++;
	}
	(data())->i = (data())->j;
	if (!(data())->p_index->str[(data())->i])
		(data())->i--;
	return (ret);
}

int	rm_quotes(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		(data())->i = -1;
		while ((data())->p_index->str[++(data())->i])
			if ((data())->p_index->str[(data())->i] == S_QUOTE
				|| (data())->p_index->str[(data())->i] == D_QUOTE)
				if (!quote_finded((data())->p_index->str[(data())->i], 1))
					return (0);
		(data())->p_index = (data())->p_index->next;
	}
	return (1);
}
