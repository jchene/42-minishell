/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:51:05 by jchene            #+#    #+#             */
/*   Updated: 2022/07/15 18:47:45 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Allocate exec struc tab, exec strucs and child id tab
int	init_exec(void)
{
	(data())->exec_struc = (t_exec *)ft_calloc(sizeof(t_exec));
	if (!(data())->exec_struc)
		return (0);
	return (1);
}

//Allocate exec to_close tab
int	init_close(t_parsing *cursor, t_exec *struc)
{
	int			to_close;

	to_close = 4;
	to_close += count_block_flags(cursor, HRD);
	struc->to_close = (int *)malloc(sizeof(int) * to_close);
	if (!struc->to_close)
		return (0);
	return (1);
}
