/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:48:08 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 18:27:01 by jchene           ###   ########.fr       */
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
	while (string && string[0] && dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp && !free_ptabn((void **)dirs))
			return (NULL);
		path = ft_strjoin(tmp, string);
		free(tmp);
		if (!path && !free_ptabn((void **)dirs))
			return (NULL);
		if (!access(path, X_OK) && !free_ptabn((void **)dirs))
			return (set_path(path, struc));
		if (!access(path, F_OK) && !free_ptabn((void **)dirs) && ifree(path, 1))
			return ((void *)display_error(ER_CMD_PE, string, CMD_NO_X) + 1);
		free(path);
	}
	free_ptabn((void **)dirs);
	display_error(ER_CMD_FO, string, CMD_NO_F);
	return ((void *)1);
}

char	*check_dat_cmd(char *string)
{
	if (is_directory(string))
		return ((void *)display_error(ER_CMD_DI, string, CMD_NO_X) + 1);
	if (ft_ischarset(string, '/'))
	{
		if (!access(string, X_OK))
			return ((void *)1);
		if (!access(string, F_OK))
			return ((void *)display_error(ER_CMD_PE, string, CMD_NO_X) + 1);
		return ((void *)display_error(ER_CMD_PA, string, CMD_NO_F) + 1);
	}
	if (is_builtin(string))
		return ((void *)1);
	return (NULL);
}

//Returns path of executable in string if found, NULL otherwise
char	*get_path(char *string, t_exec *struc, char **envp)
{
	char	**dirs;
	char	*path;

	path = ft_strdup(string);
	if (!path)
		return (NULL);
	set_path(path, struc);
	if (check_dat_cmd(string))
		return ((void *)1);
	free(path);
	set_path(NULL, struc);
	if (get_env_index("PATH", envp) != -1)
		dirs = ft_split(envp[get_env_index("PATH", envp)], ':');
	else
		return ((void *)display_error(ER_CMD_PA, string, CMD_NO_F) + 1);
	if (!dirs)
		return (NULL);
	return (try_path(string, struc, dirs, NULL));
}
