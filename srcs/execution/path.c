/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:54:24 by jchene            #+#    #+#             */
/*   Updated: 2022/07/21 00:14:17 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Sets struc path and first arg to path and executable name
char	*set_path(char *path, t_exec *struc)
{
	int		i;
	int		j;
	char	*f_arg;

	struc->path = path;
	i = -1;
	j = 0;
	while (path[++i])
		if (path[i] == '/')
			j = i + 1;
	f_arg = (char *)ft_calloc(sizeof(char) * (ft_strlen(&path[j]) + 1));
	if (!f_arg)
		return (NULL);
	ft_strcpy(&path[j], f_arg);
	struc->args[0] = f_arg;
	return (f_arg);
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

//Returns path of executable in string if found, NULL otherwise
char	*get_path(char *string, t_exec *struc, char **envp)
{
	int		i;
	char	**dirs;
	char	*tmp;
	char	*path;

	i = -1;
	while (string[++i])
		if (string[i] == '/')
			return (set_path(string, struc));
	dirs = ft_split(envp[get_env_index("PATH", envp)], ':');
	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin(tmp, string);
		free(tmp);
		if (!access(path, F_OK))
		{
			set_path(path, struc);
			free_ptabn((void **)dirs);
			return (struc->path);
		}
		free(path);
	}
	free_ptabn((void **)dirs);
	printf("minishell: command not found: %s\n", string);
	return ((void *)1);
}

//Add argument to arg tab in struc, returns argument of NULL if error occurs
char	*add_arg(char *str, t_exec *struc)
{
	int		i;
	char	*ret;

	i = 0;
	while (struc->args[i])
		i++;
	ret = (char *)ft_calloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	ft_strcpy(str, ret);
	struc->args[i] = ret;
	return (ret);
}

//Get cmd and args of block and put them in struc, returns args or NULL
char	**get_args(t_parsing *cursor, t_exec *struc, char **envp)
{
	char		**args;
	t_parsing	*tmp;

	tmp = cursor;
	args = (char **)ft_calloc(sizeof(char *)
			* (count_block_flags(tmp, ARG) + 2));
	if (!args)
		return (NULL);
	struc->args = args;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	while (tmp && tmp->flag != PIP)
	{
		if (tmp->flag == CMD)
			if (!get_path(tmp->str, struc, envp))
				return (NULL);
		if (tmp->flag == ARG)
			if (!add_arg(tmp->str, struc))
				return (NULL);
		tmp = tmp->next;
	}
	return (args);
}
