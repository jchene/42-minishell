/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:24:42 by jchene            #+#    #+#             */
/*   Updated: 2022/08/06 06:29:57 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Free un tableau de pointeurs tab de taille size
int	free_ptab(void **tab, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if ((tab)[i])
			free((tab)[i]);
	free(tab);
	return (0);
}

//Free un tableau de pointeurs tab terminé par un élément NULL
int	free_ptabn(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free((tab)[i]);
	free(tab);
	return (0);
}

//Retourne l'addresse d'une zone memoire allouee et remplie de 0
void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
	{
		perror("Error ");
		return (NULL);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}

//Remplis la zone s avec le caractere c sur n elements
void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n--)
		*str++ = c;
	return (s);
}
