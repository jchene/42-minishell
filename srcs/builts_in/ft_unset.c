/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:59 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 17:59:27 by jchene           ###   ########.fr       */
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

int	check_valid_name(char *name, int *ret)
{
	int	i;

	i = -1;
	if (!name[0] || ft_isdigit(name[0]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*ret = 1;
		return (0);
	}
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*ret = 1;
			return (0);
		}
	}
	return (1);
}

void	remove_from_exp(char *name)
{
	int		size;

	size = ft_strlen(name);
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		if (ft_strncmp((data())->exp_index->str, name, size + 1)
			&& (!(data())->exp_index->str[size]
				|| (data())->exp_index->str[size] == '='))
		{
			if ((data())->exp_index->next)
				(data())->exp_index->next->prev = (data())->exp_index->prev;
			else
				(data())->exp_end = (data())->exp_index->prev;
			if ((data())->exp_index->prev)
				(data())->exp_index->prev->next = (data())->exp_index->next;
			else
				(data())->exp_end = (data())->exp_index->next;
			free((data())->exp_index->str);
			free((data())->exp_index);
			break ;
		}
		(data())->exp_index = (data())->exp_index->next;
	}
}

int	ft_unset(char **name)
{
	int		i;
	char	*temp;
	int		ret;

	i = 0;
	ret = 0;
	while (name[++i])
	{
		if (!check_valid_name(name[i], &ret))
			continue ;
		temp = ft_strjoin(name[i], "=");
		if (!temp)
			return (-1);
		(data())->i = -1;
		while ((data())->envp[++(data())->i])
			if (ft_strncmp((data())->envp[(data())->i],
					temp, ft_strlen(temp) + 1))
				if (!remove_from_envp((data())->i))
					return (ifree((void *)temp, -1));
		free(temp);
		remove_from_exp(name[i]);
	}
	return (ret);
}
