/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:53:39 by jchene            #+#    #+#             */
/*   Updated: 2022/07/11 13:02:47 by jchene           ###   ########.fr       */
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
