/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:19:20 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 18:41:47 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	fd_cd(char *dir)
{
	if (!dir || (dir && !dir[0]))
		chdir(getenv("HOME"));
	else
	{
		chdir(dir);
		if (errno)
			perror("minishell: cd");
	}
	return (errno);
}
