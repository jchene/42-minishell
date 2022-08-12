/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:49 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/12 21:15:51 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	invalid_export(char *str)
{
	if (!(data())->in_child)
	{	
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

int	envp_will_change(char *str)
{
	(data())->temp = ft_strndup(str, (data())->i + 1, 0);
	if (!(data())->temp)
		return (0);
	if (!is_in_env((data())->temp))
	{
		if (!add_to_exp_struct(str))
			return (0);
		free((data())->temp);
		(data())->temp = NULL;
		if (!str[(data())->i])
			return (1);
		(data())->old_envp = cp_str_tab2((data())->envp);
		if (!(data())->old_envp)
			return (0);
		free_str_tab2((data())->envp);
		(data())->envp = add_to_envp(str, NULL);
		free_str_tab2((data())->old_envp);
		(data())->envp_size++;
	}
	else if (!update_env(str))
		return (0);
	if (!(data())->envp)
		return (0);
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
	return (0);
}

int	ft_export(char **str, int fd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!str[1])
		return (print_exp_struct(fd));
	while (!fd && str[++i])
	{	
		if (str[i][0] == '_' && str[i][1] == '=')
			continue ;
		if (!str[i][0] || str[i][0] == '=' || ft_isdigit(str[i][0]))
			ret = invalid_export(str[i]);
		(data())->i = -1;
		while (str[i][++(data())->i] && str[i][(data())->i] != '=')
			if (!ft_isalnum(str[i][(data())->i]) && str[i][(data())->i] != '_')
				ret = invalid_export(str[i]);
		if (!envp_will_change(str[i]))
			return (-1);
	}
	return (ret);
}
