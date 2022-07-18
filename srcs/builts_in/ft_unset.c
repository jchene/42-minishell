/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:59 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 18:42:05 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	remove_from_envp(int i)
{
	free((data())->envp[i]);
	(data())->envp[i] = NULL;
	if ((data())->envp[i + 1])
	{
		(data())->envp[i] = ft_strdup((data())->envp[i + 1]);
		if (!(data())->envp[i])
			return (str_tab2_fucked_up
				((data())->envp, (data())->envp_size));
	}
	while ((data())->envp[++i])
	{
		free((data())->envp[i]);
		(data())->envp[i] = NULL;
		if ((data())->envp[i + 1])
		{
			(data())->envp[i] = ft_strdup((data())->envp[i + 1]);
			if (!(data())->envp[i])
				return (str_tab2_fucked_up
					((data())->envp, (data())->envp_size));
		}
	}
	return (1);
}

int	ft_unset(char *name)
{
	if (!is_in_env(name))
		return (1);
	(data())->i = -1;
	while ((data())->envp[++(data())->i])
		if (ft_strchr((data())->envp[(data())->i], name) != -1)
			if (!remove_from_envp((data())->i))
				return (-1);
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		if (ft_strchr((data())->exp_index->str, name) != -1)
		{
			(data())->exp_index->next->prev = (data())->exp_end->prev;
			(data())->exp_index->prev->next = (data())->exp_end->next;
			free((data())->exp_index->str);
			free((data())->exp_index);
			break ;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
	return (0);
}
