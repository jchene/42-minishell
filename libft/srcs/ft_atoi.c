/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 23:56:48 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 18:36:29 by jchene           ###   ########.fr       */
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
		nbr += nptr[i] - 48;
		i++;
	}
	return (nbr * neg);
}
