/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:31:33 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/08 19:48:20 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_in_env(char *to_find)
{
	int	i;

	i = -1;
	while ((data())->envp[++i])
		if (ft_strncmp((data())->envp[i], to_find, ft_strlen(to_find) + 1))
			return (1);
	return (0);
}

int	fill_new_envp(char **dst, int size)
{
	int	i;

	i = -1;
	while (++i < size - 1)
	{
		dst[i] = ft_strdup((data())->old_envp[i]);
		if (!dst[i])
		{
			while (dst[--i])
				free(dst[i]);
			free(dst);
			return (0);
		}
	}
	return (1);
}

char	**add_to_envp(char *new, char **dst)
{
	dst = malloc(sizeof(char *) * ((data())->envp_size + 2));
	if (!dst)
		return (NULL);
	dst[(data())->envp_size + 1] = NULL;
	dst[(data())->envp_size] = ft_strdup(new);
	if (!dst[(data())->envp_size])
	{
		free(dst);
		return (0);
	}
	if (!fill_new_envp(dst, (data())->envp_size + 1))
		return (NULL);
	return (dst);
}

int	update_exp_struct(char *new)
{
	int		size;

	if ((data())->temp)
		free((data())->temp);
	(data())->temp = ft_strndup(new, (data())->i, 0);
	if (!(data())->temp)
		return (0);
	size = ft_strlen((data())->temp);
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		if (ft_strncmp((data())->exp_index->str, (data())->temp, size + 1)
			&& (!(data())->exp_index->str[size]
				|| (data())->exp_index->str[size] == '='))
		{
			free((data())->exp_index->str);
			(data())->exp_index->str = envp_to_export(new, 0);
			if (!(data())->exp_index->str)
				return (0);
			break ;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
	return (1);
}

int	update_env(char *new)
{
	int	i;
	int	ret;

	i = -1;
	ret = 1;
	while ((data())->envp[++i])
	{
		if (ft_strncmp((data())->envp[i],
				(data())->temp, ft_strlen((data())->temp) + 1))
		{
			free((data())->temp);
			(data())->temp = NULL;
			free((data())->envp[i]);
			(data())->envp[i] = ft_strdup(new);
			if (!(data())->envp[i])
				return (str_tab2_fucked_up
					(&(data())->envp, (data())->envp_size));
			break ;
		}
	}
	ret = update_exp_struct(new);
	if ((data())->temp)
		free((data())->temp);
	(data())->temp = NULL;
	return (ret);
}
