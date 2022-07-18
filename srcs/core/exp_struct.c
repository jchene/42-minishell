/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:43:29 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/25 21:23:17 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_exp_struct(void)
{
	t_export	**temp;

	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		temp = &(data())->exp_index;
		(data())->exp_index = (data())->exp_index->next;
		free((*temp)->str);
		free(*temp);
		*temp = NULL;
	}
	(data())->exp_start = NULL;
	(data())->exp_index = (data())->exp_end;
	while ((data())->exp_index)
	{
		temp = &(data())->exp_index;
		(data())->exp_index = (data())->exp_index->prev;
		free((*temp)->str);
		free(*temp);
		*temp = NULL;
	}
	(data())->exp_end = NULL;
	return (0);
}

int	add_to_exp_struct(char *str)
{
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index->next)
		(data())->exp_index = (data())->exp_index->next;
	(data())->exp_index->next = malloc(sizeof(t_export));
	if (!(data())->exp_index->next)
		return (0);
	(data())->exp_index->next->str = ft_strdup(str);
	if (!(data())->exp_index->next->str)
		return (0);
	(data())->exp_index->next->next = NULL;
	(data())->exp_index->next->prev = (data())->exp_index;
	(data())->exp_end = (data())->exp_index->next;
	return (1);
}

int	swap_that(char **str1, char **str2)
{
	char		*temp;

	temp = ft_strdup(*str1);
	if (!temp)
		return (0);
	free(*str1);
	*str1 = ft_strdup(*str2);
	if (!*str1)
	{
		free(temp);
		free_exp_struct();
		return (0);
	}
	free(*str2);
	*str2 = ft_strdup(temp);
	free(temp);
	if (!*str2)
	{
		free_exp_struct();
		return (0);
	}
	return (1);
}

int	sort_exp_struct(void)
{
	t_export	*index;
	int			i;

	(data())->exp_index = (data())->exp_index;
	while ((data())->exp_index->next)
	{
		index = (data())->exp_index;
		while (index)
		{
			i = -1;
			while (index->str[++i] && (data())->exp_index->str[i])
				if (index->str[i] != (data())->exp_index->str[i])
					break ;
			if ((data())->exp_index->str[i])
				if (!index->str[i]
					|| (index->str[i] < (data())->exp_index->str[i]))
					if (!swap_that(&index->str, &(data())->exp_index->str))
						return (0);
			index = index->next;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
	return (1);
}

int	create_exp_struct(void)
{
	if (!(data())->envp)
		return (1);
	(data())->exp_start = malloc(sizeof(t_export));
	if (!(data())->exp_start)
		return (0);
	(data())->i = 0;
	(data())->exp_index = (data())->exp_start;
	(data())->exp_index->str = ft_strdup((data())->envp[(data())->i]);
	(data())->exp_index->prev = NULL;
	(data())->exp_index->next = NULL;
	while ((data())->envp[++(data())->i])
	{
		(data())->exp_index->next = malloc(sizeof(t_export));
		if (!(data())->exp_index->next)
			return (0);
		(data())->exp_index->next->prev = (data())->exp_index;
		(data())->exp_index->next->str
			= ft_strdup((data())->envp[(data())->i]);
		(data())->exp_index->next->next = NULL;
		(data())->exp_index = (data())->exp_index->next;
	}
	(data())->exp_end = (data())->exp_index;
	return (sort_exp_struct());
}
