/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab2_fucked_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:52:18 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/19 17:06:26 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Free TAB et son contenu
int	str_tab2_fucked_up(char	**tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (tab[i])
			free(tab[i]);
	free(tab);
	return (0);
}
