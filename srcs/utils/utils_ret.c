/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:53:39 by jchene            #+#    #+#             */
/*   Updated: 2022/08/06 07:49:41 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Perrors the string str and returns ret ads an int
int	iperror(const char *str, int ret)
{
	perror(str);
	return (ret);
}

//Perrors the string str and returns NULL
void	*pperror(const char *str)
{
	perror(str);
	return (NULL);
}

//Frees ptr and returns ret as an int
int	ifree(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

//Frees ptr and return ret as a pointer
void	*pfree(void *ptr, void *ret)
{
	free(ptr);
	return (ret);
}
