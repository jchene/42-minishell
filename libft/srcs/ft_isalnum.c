/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 05:14:32 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 03:28:58 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Return positif si C est un caractère alphanumérique, sinon 0
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
