/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_finded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:39:32 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 17:58:34 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	lonely_dollar(t_quotes *index, int i)
{
	while (index)
	{
		if (i == index->quoted_from && i == index->quoted_to)
			return (1);
		index = index->next;
	}
	return (0);
}

int	replace_by_exit_code(void)
{
	char	*old;
	char	*buff;
	int		ret;

	old = NULL;
	buff = NULL;
	ret = replace_it(1, &old, &buff);
	return (return_it(ret, &old, &buff, 0));
}

int	check_for_insta_return_bis(void)
{
	if ((data())->p_index->str[(data())->i + 1] == '?')
	{
		(data())->j += 2;
		(data())->temp = ft_itoa((data())->exit_code);
		if (!(data())->temp)
			return (-1);
		return (replace_by_exit_code());
	}
	if (ft_isdigit((data())->p_index->str[(data())->i + 1]))
	{
		(data())->j += 2;
		(data())->temp = ft_strdup("");
		if (!(data())->temp)
			return (-1);
		return (replace_by_exit_code());
	}
	return (0);
}

int	check_for_insta_return(void)
{
	if (lonely_dollar((data())->p_index->quotes, (data())->i))
	{
		(data())->j++;
		(data())->temp = ft_strdup("");
		if (!(data())->temp)
			return (-1);
		return (replace_by_exit_code());
	}
	if (!(data())->p_index->str[(data())->j + 1]
		|| (!ft_isalnum((data())->p_index->str[(data())->j + 1])
			&& (data())->p_index->str[(data())->j + 1] != '_'
			&& (data())->p_index->str[(data())->j + 1] != '?'))
		return (1);
	return (check_for_insta_return_bis());
}

int	dollar_finded(int ret)
{
	ret = check_for_insta_return();
	if (ret == -1)
		return (0);
	if (ret == 1)
		return (1);
	(data())->old = was_quoted((data())->p_index->quotes, (data())->j);
	while ((data())->p_index->str[(data())->j])
	{
		(data())->j++;
		if (!(data())->p_index->str[(data())->j]
			|| (!ft_isalnum((data())->p_index->str[(data())->j])
				&& (data())->p_index->str[(data())->j] != '_')
			|| was_quoted((data())->p_index->quotes, (data())->j)
			!= (data())->old)
		{
			(data())->temp = ft_strndup((data())->p_index->str,
					(data())->j - (data())->i - 1, (data())->i + 1);
			if (!(data())->temp)
				return (0);
			return (convert_it(ft_strlen((data())->temp), -1, 0));
		}
	}
	return (1);
}
