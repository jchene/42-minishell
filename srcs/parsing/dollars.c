/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:44:23 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 12:45:10 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	return_it(int ret, char **old, char **buff)
{
	if (*old)
		free(*old);
	if (*buff)
		free(*buff);
	if ((data())->temp)
		free((data())->temp);
	(data())->temp = NULL;
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
	if (!(data())->temp[0] || !finded)
		(data())->i--;
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
	return (return_it(ret, &old, &buff));
}

int	replace_by_exit_code(void)
{
	char	*old;
	char	*buff;
	int		ret;

	old = NULL;
	buff = NULL;
	ret = replace_it(1, &old, &buff);
	return (return_it(ret, &old, &buff));
}

int	dollar_finded(void)
{
	if ((data())->p_index->str[(data())->i] == '$'
		&& (data())->p_index->str[(data())->i + 1]
		&& (data())->p_index->str[(data())->i + 1] == '?')
	{
		(data())->j += 2;
		(data())->temp = ft_itoa((data())->exit_code);
		if (!(data())->temp)
			return (0);
		return (replace_by_exit_code());
	}
	if ((data())->p_index->str[(data())->i] == '$'
		&& (data())->p_index->str[(data())->i + 1]
		&& ft_isdigit((data())->p_index->str[(data())->i + 1]))
	{
		(data())->j += 2;
		(data())->temp = ft_strdup("");
		if (!(data())->temp)
			return (0);
		return (replace_by_exit_code());
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
			if (!(data())->temp[0]
				&& (!(data())->p_index->str[(data())->j]
					|| (data())->p_index->str[(data())->j] == ' '
					|| (data())->p_index->str[(data())->j] == '\t'
					|| ((data())->p_index->str[(data())->j] == D_QUOTE
						&& (data())->j - 2 >= 0
						&& ((data())->p_index->str[(data())->j - 2] == D_QUOTE))))
			{
				free((data())->temp);
				(data())->temp = NULL;
				return (1);
			}
			return (convert_it(ft_strlen((data())->temp), -1, 0));
		}
	}
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
		(data())->i = -1;
		while ((data())->p_index->str[++(data())->i])
			if ((data())->p_index->str[(data())->i] == '$'
				&& set_int(&(data())->j, (data())->i, 1)
				&& (from_hrd || (!from_hrd && !is_quoted(((data())->j), 0))))
				if (!dollar_finded())
					return (0);
		if (!from_hrd && !(data())->p_index->str[0])
		{
			temp = NULL;
			if ((data())->p_index->prev)
			{
				if ((data())->p_index->next)
				{
					(data())->p_index->prev->next = (data())->p_index->next;
					(data())->p_index->next->prev = (data())->p_index->prev;
				}
				else
					(data())->p_index->prev->next = NULL;
				temp = (data())->p_index->prev;
			}
			else if ((data())->p_index->next)
			{
				(data())->p_index->next->prev = NULL;
				(data())->p_start = (data())->p_index->next;
				free((data())->p_index->str);
				free((data())->p_index);
				(data())->p_index = temp;
				continue ;
			}
			else
				(data())->p_start = NULL;
			free((data())->p_index->str);
			free((data())->p_index);
			(data())->p_index = temp;
		}
		if ((data())->p_index)
			(data())->p_index = (data())->p_index->next;
	}
	return (1);
}
