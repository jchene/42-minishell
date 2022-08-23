/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libexec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:16:34 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 18:33:23 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_builtin(char *str)
{
	if (!str || !str[0])
		return (-1);
	if (ft_strcmp(str, "cd"))
		return (1);
	if (ft_strcmp(str, "env"))
		return (2);
	if (ft_strcmp(str, "echo"))
		return (3);
	if (ft_strcmp(str, "exit"))
		return (4);
	if (ft_strcmp(str, "export"))
		return (5);
	if (ft_strcmp(str, "pwd"))
		return (6);
	if (ft_strcmp(str, "unset"))
		return (7);
	return (0);
}
