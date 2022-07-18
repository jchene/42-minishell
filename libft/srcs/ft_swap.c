/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:47:51 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 02:29:55 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Echange les valeurs int de PTR1 et PTR2
void	ft_swap(int *ptr1, int *ptr2)
{
	int	temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
