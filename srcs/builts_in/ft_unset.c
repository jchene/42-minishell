/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:59 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 11:06:13 by anguinau         ###   ########.fr       */
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
				(&(data())->envp, (data())->envp_size));
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
					(&(data())->envp, (data())->envp_size));
		}
	}
	(data())->envp_size--;
	return (1);
}

int	check_valid_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd("%s", 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
	}
	return (1);
}

void	remove_from_exp(char *name)
{
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		if (ft_strchr((data())->exp_index->str, name) != -1)
		{
			(data())->exp_index->next->prev = (data())->exp_index->prev;
			(data())->exp_index->prev->next = (data())->exp_index->next;
			free((data())->exp_index->str);
			free((data())->exp_index);
			break ;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
}

int	ft_unset(char **name)
{
	int	i;

	i = 0;
	while (name && name[0] && name[++i])
	{	
		if (!check_valid_name(name[i]))
			return (-1);
		if ((data())->envp && is_in_env(name[i]))
		{
			(data())->i = -1;
			while ((data())->envp[++(data())->i])
				if (ft_strchr((data())->envp[(data())->i], name[i]) != -1)
					if (!remove_from_envp((data())->i))
						return (-1);
		}
		remove_from_exp(name[i]);
	}
	return (0);
}
