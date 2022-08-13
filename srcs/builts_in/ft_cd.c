/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:20 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 18:15:09 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*get_home(void)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while ((data())->envp[++i])
	{
		if (ft_strncmp((data())->envp[i], "HOME=", 6))
		{
			s = ft_strndup((data())->envp[i], ft_strlen((data())->envp[i]), 5);
			if (!s)
				return (NULL);
		}
	}
	if (!s)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (s);
}

char	*get_current_dir(char *buff, int size)
{
	buff = malloc(sizeof(char) * size);
	if (!buff)
		return (NULL);
	while (!getcwd(buff, size))
	{
		free(buff);
		size++;
		buff = malloc(sizeof(char) * size);
		if (!buff)
			return (NULL);
	}
	return (buff);
}

int	update_pwd(int i, char *cd, char **str)
{
	str = malloc(sizeof(char *) * 4);
	if (!str)
		return (1);
	str[3] = NULL;
	str[2] = NULL;
	str[1] = NULL;
	str[0] = NULL;
	while ((data())->envp[++i])
	{
		if (ft_strncmp((data())->envp[i], "PWD=", 5))
		{
			str[1] = ft_strjoin("OLD", (data())->envp[i]);
			if (!str[1])
				return (free_ptab((void **)str, 4) - 1);
			cd = get_current_dir(NULL, 1);
			str[2] = ft_strjoin("PWD=", cd);
			free(cd);
			if (!str[2])
				return (free_ptab((void **)str, 4) - 1);
			if (ft_export(str, 2))
				return (free_ptab((void **)str, 4) - 1);
		}
	}
	return (free_ptab((void **)str, 4));
}

int	ft_cd(char **dir, char *str)
{
	if (dir[1] && dir[2]
		&& ft_putstr_fd("bash: cd: too many arguments\n", 2) >= 0)
		return (1);
	if (!dir[1] || (dir[1] && !dir[1][0]))
	{
		str = get_home();
		if (!str)
			return (1);
		if (chdir(str))
		{
			free(str);
			perror("minishell: cd");
			return (1);
		}
		free(str);
		update_pwd(-1, NULL, NULL);
		return (0);
	}
	if (chdir(dir[1]))
	{
		perror("minishell: cd");
		return (1);
	}
	update_pwd(-1, NULL, NULL);
	return (0);
}
