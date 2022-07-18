/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:54:43 by anguinau          #+#    #+#             */
/*   Updated: 2022/01/28 02:54:43 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Return l'index du début de TO_FIND si il est trouvé dans STR, sinon -1
int	ft_strchr(char *str, const char *to_find)
{
	int	i;
	int	j;
	int	reset;

	i = -1;
	while (str[++i])
	{
		j = 0;
		reset = 0;
		while (str[i] && to_find[j] && str[i] == to_find[j])
		{
			reset++;
			i++;
			j++;
		}
		if (!to_find[j])
			return (i - reset);
		if (!str[i])
			return (-1);
		i -= reset;
	}
	return (-1);
}
