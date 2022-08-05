/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:20 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 11:07:43 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	get_home(char **str)
{
	int		i;

	i = -1;
	while ((data())->envp && (data())->envp[++i])
	{
		if (ft_strchr((data())->envp[i], "HOME") != -1)
		{
			*str = ft_strndup((data())->envp[i],
					ft_strlen((data())->envp[i] - 5), 5);
			if (!*str)
				return (0);
		}
	}
	if (!*str)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (1);
}

int	ft_cd(char **dir)
{
	char	*str;

	if ((dir[2]) && ft_putstr_fd("bash: cd: too many arguments", 2) >= 0)
		return (1);
	if (!dir[1] || (dir[1] && !dir[1][0]))
	{
		str = NULL;
		if (!get_home(&str))
			return (-1);
		if (!str)
			return (1);
		if (chdir(str))
		{
			free(str);
			perror("minishell: cd");
			return (1);
		}
		free(str);
	}
	else if (chdir(dir[1]))
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
