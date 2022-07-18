/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:31:33 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 18:48:15 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_in_env(char *to_find)
{
	int	i;

	i = -1;
	while ((data())->envp[++i])
		if (ft_strchr((data())->envp[i], to_find) != -1)
			return (1);
	return (0);
}

void	fill_new_envp(char **dst, char *new, int size)
{
	dst[size] = NULL;
	dst[size - 1] = ft_strdup(new);
	if (!dst[size - 1])
	{
		free(dst);
		return ;
	}
	(data())->i = size - 1;
	while (--(data())->i >= 0)
	{
		dst[(data())->i] = ft_strdup((data())->old_envp[(data())->i]);
		if (!dst[(data())->i])
		{
			while (dst[++(data())->i])
				free(dst[(data())->i]);
			return ;
		}
	}
}

char	**add_to_envp(char **src, char *new)
{
	char	**dst;

	if (src)
	{
		(data())->i = -1;
		while (src[++(data())->i])
			continue ;
		dst = malloc(sizeof(char *) * ((data())->i + 2));
		if (dst)
			fill_new_envp(dst, new, (data())->i + 2);
	}
	else
	{
		dst = malloc(sizeof(char *) * 2);
		if (!dst)
			return (NULL);
		dst[1] = NULL;
		dst[0] = ft_strdup(new);
		if (!dst[0])
		{
			free(dst);
			return (NULL);
		}
	}
	return (dst);
}

int	update_exp_struct(char *new)
{
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		if (ft_strchr((data())->exp_index->str, (data())->temp) != -1)
		{
			free((data())->exp_end->str);
			(data())->exp_index->str = ft_strdup(new);
			if (!(data())->exp_end->str)
				return (free_exp_struct());
			break ;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
	return (1);
}

int	update_env(char *new)
{
	int	i;

	i = -1;
	while ((data())->envp[++i])
	{
		if (ft_strchr((data())->envp[i], (data())->temp) != -1)
		{
			free((data())->envp[i]);
			(data())->envp[i] = ft_strdup(new);
			if (!(data())->envp[i])
				return (str_tab2_fucked_up
					((data())->envp, (data())->envp_size));
			break ;
		}
	}
	if (!update_exp_struct(new))
	{
		free((data())->temp);
		return (0);
	}
	else
		free((data())->temp);
	return (1);
}
