/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 23:56:48 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 03:19:21 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Return un long long à partir de NPTR
long long	ft_atoi(const char *nptr)
{
	long long	nbr;
	int			neg;
	int			i;

	nbr = 0;
	neg = 1;
	i = 0;
	if (nptr[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr *= 10;
		nbr += (int)*nptr - 48;
		i++;
	}
	return (nbr * neg);
}
