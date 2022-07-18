/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:49 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/06 14:28:15 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	invalid_export(char *str)
{
	ft_putstr_fd("bash: export: `", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	return (-1);
}

int	envp_will_change(char *str)
{
	(data())->temp = ft_strndup(str, (data())->i, 0);
	if (!(data())->temp)
		return (0);
	if (!(data())->envp)
		(data())->envp = add_to_envp(NULL, str);
	else if (!is_in_env((data())->temp))
	{
		free((data())->temp);
		(data())->old_envp = cp_str_tab2((data())->envp);
		if (!(data())->old_envp)
			return (0);
		free_str_tab2((data())->envp);
		(data())->envp = add_to_envp((data())->old_envp, str);
		if (!(data())->envp)
			return (0);
		free_str_tab2((data())->old_envp);
	}
	else if (!update_env(str))
		return (0);
	if (!(data())->envp)
		return (0);
	return (1);
}

void	print_exp_struct(void)
{
	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		printf("export %s\n", (data())->exp_index->str);
		(data())->exp_index = (data())->exp_index->next;
	}		
}

int	ft_export(char *str)
{
	if (!str)
		print_exp_struct();
	else
	{
		(data())->i = -1;
		while (str[++(data())->i] && str[(data())->i] != '=')
			if (!ft_isalnum(str[(data())->i]) && str[(data())->i] != '_')
				return (invalid_export(str));
		if (str[(data())->i] && !envp_will_change(str))
			return (0);
		if (!(data())->exp_start)
		{
			(data())->exp_start = malloc(sizeof(t_export));
			if (!(data())->exp_start)
				return (0);
			(data())->exp_start->str = str;
			(data())->exp_start->prev = NULL;
			(data())->exp_start->next = NULL;
		}
		else
			add_to_exp_struct(str);
	}
	return (1);
}
