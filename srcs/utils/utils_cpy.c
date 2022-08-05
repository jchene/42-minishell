/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:57:55 by jchene            #+#    #+#             */
/*   Updated: 2022/08/03 05:52:26 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ft_strcpy(char *src, char *dst)
{
	while (*src)
		*dst++ = *src++;
	*dst++ = *src++;
}

int	ft_strmcpy(char *src, char **dst)
{
	*dst = (char *)ft_calloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!*dst)
		return (0);
	ft_strcpy(src, *dst);
	return (1);
}

int	strict_cmp(char *s1, char *s2)
{
	if ((!s1 && s2) || (s1 && !s2))
		return (0);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (0);
	if (*s1 || *s2)
		return (0);
	return (1);
}
