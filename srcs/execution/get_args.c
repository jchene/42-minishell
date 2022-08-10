/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:54:24 by jchene            #+#    #+#             */
/*   Updated: 2022/08/09 02:36:46 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
char	**get_args(t_parsing *tmp, t_exec *struc, char **envp)
{
	char		**args;

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
	return ((void *)1);
}
