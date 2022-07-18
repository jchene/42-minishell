/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:04:54 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 03:13:09 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Write S dans FD
int	ft_putstr_fd(char *s, int fd)
{
	while (s && *s++)
		write(fd, (s - 1), 1);
	return (1);
}
