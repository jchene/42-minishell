/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:44:23 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 15:39:08 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_quoted(int k, int quote)
{
	while (--k >= 0 && !quote)
		if ((data())->p_index->str[k] == S_QUOTE)
			quote = 1;
	if (quote)
	{
		k = (data())->j;
		while (quote != 2 && (data())->p_index->str[++k])
			if ((data())->p_index->str[k] == S_QUOTE)
				quote = 2;
		if (quote == 2)
			return (1);
	}
	return (0);
}

int	replace_it(int finded, char **old, char **buff)
{
	*old = ft_strdup((data())->p_index->str);
	if (!*old)
		return (0);
	free((data())->p_index->str);
	(data())->p_index->str = ft_strndup(*old, (data())->i, 0);
	if (!(data())->p_index->str)
		return (0);
	if (finded)
		*buff = ft_strjoin((data())->p_index->str, (data())->temp);
	else
		*buff = ft_strjoin((data())->p_index->str, "");
	if (!*buff)
		return (0);
	free((data())->temp);
	(data())->temp = ft_strndup(*old, ft_strlen(*old), (data())->j);
	if (!(data())->temp)
		return (0);
	free((data())->p_index->str);
	(data())->p_index->str = ft_strjoin(*buff, (data())->temp);
	if (!(data())->p_index->str)
		return (0);
	return (1);
}

int	convert_it(int size, int k, int finded)
{
	char	*old;
	char	*buff;
	int		ret;

	old = NULL;
	buff = ft_strjoin((data())->temp, "=");
	if (!buff)
		return (0);
	while (!finded && (data())->envp[++k])
		if (ft_strncmp((data())->envp[k], buff, size + 2))
			finded = 1;
	free(buff);
	buff = NULL;
	if (finded)
	{
		free((data())->temp);
		(data())->temp = ft_strndup((data())->envp[k],
				ft_strlen((data())->envp[k]) - (size + 1), size + 1);
		if (!(data())->temp)
			return (0);
	}
	ret = replace_it(finded, &old, &buff);
	if (old)
		free(old);
	if (buff)
		free(buff);
	if ((data())->temp)
		free((data())->temp);
	return (ret);
}

int	dollar_finded(void)
{
	if (ft_strcmp((data())->p_index->str, "$?"))
	{
		free((data())->p_index->str);
		(data())->p_index->str = ft_itoa((data())->exit_code);
		if (!(data())->p_index->str)
			return (0);
		return (1);
	}
	while ((data())->p_index->str[(data())->j])
	{
		(data())->j++;
		if (!(data())->p_index->str[(data())->j]
			|| (!ft_isalnum((data())->p_index->str[(data())->j])
				&& (data())->p_index->str[(data())->j] != '_'))
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

int	rm_dollars(t_parsing *start, t_parsing *temp, int from_hrd)
{
	(data())->p_index = start;
	temp = (data())->p_start;
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
		}
		(data())->i = -1;
		while ((data())->p_index->str[++(data())->i])
			if ((data())->p_index->str[(data())->i] == '$'
				&& set_int(&(data())->j, (data())->i, 1)
				&& (from_hrd || (!from_hrd && !is_quoted(((data())->j), 0))))
				if (!dollar_finded())
					return (0);
		(data())->p_index = (data())->p_index->next;
	}
	return (1);
}
