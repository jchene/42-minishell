/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:57:49 by jchene            #+#    #+#             */
/*   Updated: 2022/08/01 22:05:55 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Set l'int situé à l'addresse dst à la valeur de src et retourne ret
int	set_int(int *dst, int src, int ret)
{
	*dst = src;
	return (ret);
}

//Set le char situé à l'addresse dst à la valeur de c et retourne ret
int	set_char(char *dst, char src, int ret)
{
	*dst = src;
	return (ret);
}

int	set_ptr(void **dst, void *src, int ret)
{
	*dst = src;
	return (ret);
}

//Set le char situé à l'addresse dst à la valeur de c si vide et retourne ret
int	fill_char(char *dst, char c, int ret)
{
	if (!(*dst))
		*dst = c;
	return (ret);
}
