/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:05:27 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 11:21:24 by anguinau         ###   ########.fr       */
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
	(data())->envp[2] = ft_strdup("_=/usr/bin/env");
	(data())->envp[3] = NULL;
	(data())->envp_size = 3;
	return (1);
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
			(data())->i++;
		(data())->envp_size = (data())->i;
	}
	else if (!new_envp())
			return (0);
	return (1);
}

int	init_data(char **envp)
{
	data();
	(data())->stop = 0;
	(data())->exit_code = 0;
	(data())->got_from_builtsin = 0;
	(data())->line = NULL;
	(data())->envp = NULL;
	(data())->envp_size = 0;
	(data())->h_start = NULL;
	(data())->p_start = NULL;
	(data())->exp_start = NULL;
	(data())->exp_end = NULL;
	(data())->he_start = NULL;
	(data())->he_read = 0;
	(data())->lines_executed = 1;
	if (!create_envp(envp))
		return (0);
	return (1);
}
