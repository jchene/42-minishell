/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:48:08 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/05 17:36:57 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Sets struc path and first arg to path and executable name
char	*set_path(char *path, t_exec *struc)
{
	struc->path = path;
	struc->args[0] = path;
	return ((void *)1);
}

//Returns index of an env name in envp, -1 if not found
int	get_env_index(char *env_name, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (env_name[j] && envp[i][j] && env_name[j] == envp[i][j])
			j++;
		if (envp[i][j] && envp[i][j] == '=')
			return (i);
	}
	return (-1);
}

char	*try_path(char *string, t_exec *struc, char **dirs, char *path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp && !free_ptabn((void **)dirs))
			return ((void *)0);
		path = ft_strjoin(tmp, string);
		free(tmp);
		if (!path && !free_ptabn((void **)dirs))
			return ((void *)0);
		if (!access(path, F_OK) && !free_ptabn((void **)dirs))
			return (set_path(path, struc));
		free(path);
	}
	free_ptabn((void **)dirs);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": command not found\n", 2);
	(data())->exit_code = 127;
	(data())->skip_exec = 1;
	return ((void *)1);
}

//Returns path of executable in string if found, NULL otherwise
char	*get_path(char *string, t_exec *struc, char **envp)
{
	char	**dirs;
	char	*path;

	fprintf(stderr, "%stesting: %s%s\n", RED_CODE, string, RESET_CODE);
	if (is_builtin(string))
	{
		path = ft_strdup(string);
		if (!path)
			return (NULL);
		return (set_path(path, struc));
	}
	if (!access(string, F_OK))
	{
		path = ft_strdup(string);
		if (!path)
			return (NULL);
		return (set_path(path, struc));
	}
	dirs = ft_split(envp[get_env_index("PATH", envp)], ':');
	if (!dirs)
		return (NULL);
	return (try_path(string, struc, dirs, NULL));
}
