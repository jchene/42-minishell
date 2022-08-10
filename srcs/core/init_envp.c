/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 03:01:09 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/08 21:44:01 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	new_envp(void)
{
	(data())->envp = malloc(sizeof(char *) * 4);
	if (!(data())->envp)
		return (0);
	(data())->envp[0] = ft_strdup("PWD=/home/gekyume/minishell");
	(data())->envp[1] = ft_strdup("SHLVL=1");
	(data())->envp[2] = ft_strdup("_=./minishell");
	(data())->envp[3] = NULL;
	(data())->envp_size = 3;
	return (1);
}

int	return_upgrade(void)
{
	int	j;

	if (!(data())->envp[(data())->i])
	{
		j = (data())->i - 1;
		while (--j)
			free((data())->envp[j]);
		while ((data())->envp[++(data())->i])
			free((data())->envp[(data())->i]);
		free((data())->envp);
		(data())->envp = NULL;
		return (0);
	}
	return (1);
}

int	upgrade_shlvl(int i, int j, int lvl, char *temp)
{
	while ((data())->envp[(data())->i][++i] != '=')
		continue ;
	i++;
	while ((data())->envp[(data())->i][i + ++j])
	{
		lvl *= 10;
		lvl += (int)(data())->envp[(data())->i][i + j] - 48;
	}
	lvl++;
	(data())->shlvl = lvl;
	free((data())->envp[(data())->i]);
	temp = ft_itoa(lvl);
	if (!temp)
		return (0);
	(data())->envp[(data())->i] = ft_strjoin("SHLVL=", temp);
	free(temp);
	return (return_upgrade());
}

int	create_envp(char **envp)
{
	if (envp && envp[0])
	{
		(data())->envp = cp_str_tab2(envp);
		if (!(data())->envp)
			return (0);
		(data())->i = 0;
		while ((data())->envp[(data())->i])
		{
			if (ft_strncmp((data())->envp[(data())->i], "SHLVL=", 7))
				if (!upgrade_shlvl(-1, -1, 0, NULL))
					return (0);
			(data())->i++;
		}
		(data())->envp_size = (data())->i;
	}
	else if (!new_envp())
		return (0);
	return (1);
}
