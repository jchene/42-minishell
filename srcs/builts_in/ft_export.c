/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:49 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 11:07:57 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	invalid_export(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}

int	envp_will_change(char *str)
{
	(data())->temp = ft_strndup(str, (data())->i, 0);
	if (!(data())->temp)
		return (0);
	if (!(data())->envp)
		(data())->envp = add_to_envp(NULL, str, NULL);
	else if (!is_in_env((data())->temp))
	{
		free((data())->temp);
		(data())->old_envp = cp_str_tab2((data())->envp);
		if (!(data())->old_envp)
			return (0);
		free_str_tab2((data())->envp);
		(data())->envp = add_to_envp((data())->old_envp, str, NULL);
		free_str_tab2((data())->old_envp);
	}
	else if (!update_env(str))
		return (0);
	if (!(data())->envp)
		return (0);
	(data())->envp_size++;
	return (1);
}

int	print_exp_struct(int fd)
{
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd((data())->exp_index->str, fd);
		ft_putstr_fd("\n", fd);
		(data())->exp_index = (data())->exp_index->next;
	}
	return (-1);
}

int	ft_export(char **str, int fd)
{
	int	i;

	i = 0;
	while (str && str[++i])
	{	
		if (!str[i])
			return (print_exp_struct(fd));
		(data())->i = -1;
		while (str[i][++(data())->i] && str[i][(data())->i] != '=')
			if (!ft_isalnum(str[i][(data())->i]) && str[i][(data())->i] != '_')
				return (invalid_export(str[i]));
		if (str[i][(data())->i] && !envp_will_change(str[i]))
			return (-1);
		if (!(data())->exp_start)
		{
			(data())->exp_start = malloc(sizeof(t_export));
			if (!(data())->exp_start)
				return (-1);
			(data())->exp_start->prev = NULL;
			(data())->exp_start->next = NULL;
			(data())->exp_start->str = ft_strdup(str[i]);
			if (!(data())->exp_start->str)
				return (-1);
		}
		else if (!add_to_exp_struct(str[i]))
			return (-1);
	}
	return (0);
}
