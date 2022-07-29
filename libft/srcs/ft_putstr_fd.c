/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:04:54 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/29 18:20:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Write S dans FD
int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		if (write(fd, s[i], 1) < 0)
			return (iperror("minishell: write failed", 0));
	return (1);
}

// Write S suivi d'un '\n' dans FD
int	ft_putstrn_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		if (write(fd, s[i], 1) < 0)
			return (iperror("minishell: write failed", 0));
	if (write(fd, "\n", 1) < 0)
		return (iperror("minishell: write failed", 0));
	return (1);
}
