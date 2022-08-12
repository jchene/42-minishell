/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:42:29 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/12 20:17:39 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	update_dollars_infos(t_dollars *index)
{
	if (!(data())->p_index->dollars)
	{
		(data())->p_index->dollars = malloc(sizeof(t_dollars));
		if (!(data())->p_index->dollars)
			return (0);
		(data())->p_index->dollars->next = NULL;
		(data())->p_index->dollars->from = (data())->i;
		(data())->p_index->dollars->to = (data())->i + (data())->offset;
		return (1);
	}
	while (index->next)
		index = index->next;
	index->next = malloc(sizeof(t_dollars));
	if (!index->next)
		return (0);
	index->next->next = NULL;
	index->next->from = (data())->i;
	index->next->to = (data())->i + (data())->offset;
	return (1);
}

void	update_quotes_infos(t_quotes *index, int diff)
{
	if (index)
	{
		index->quoted_to -= diff;
		if (index->quoted_to < index->quoted_from)
		{
			(data())->p_index->quotes = (data())->p_index->quotes->next;
			free(index);
			if (!(data())->p_index->quotes)
				return ;
			index = (data())->p_index->quotes;
			index->quoted_from -= diff;
			index->quoted_to -= diff;
		}
		index = index->next;
		while (index)
		{
			index->quoted_from -= diff;
			index->quoted_to -= diff;
			index = index->next;
		}
	}
}

int	return_it(int ret, char **old, char **buff, int diff)
{
	if (*old)
		free(*old);
	if (*buff)
		free(*buff);
	if ((data())->temp)
		free((data())->temp);
	(data())->temp = NULL;
	diff = (data())->j - ((data())->i + (data())->offset);
	update_quotes_infos((data())->p_index->quotes, diff);
	if (!update_dollars_infos((data())->p_index->dollars))
		return (-1);
	(data())->i += (data())->offset - 1;
	if (!ret)
		return (-1);
	return (ret);
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
	(data())->offset = ft_strlen((data())->temp);
	if (!finded)
		(data())->offset = 0;
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
	return (return_it(ret, &old, &buff, 0));
}
