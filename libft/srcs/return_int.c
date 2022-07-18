/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:53:00 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 02:55:17 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Return N1 ou N2 selon qui est le plus grand
int	return_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

// Return N1 ou N2 selon qui est le plus petit
int	return_min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}
