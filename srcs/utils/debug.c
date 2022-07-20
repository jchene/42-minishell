/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:33:05 by jchene            #+#    #+#             */
/*   Updated: 2022/07/21 00:07:54 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	display_list(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		if ((data())->p_index->flag == INV)
			fprintf(stderr, "%s*%s* - %s%s\n", RED_CODE,
				(data())->p_index->str, flag_name((data())->p_index->flag),
				RESET_CODE);
		else
			fprintf(stderr, "%s*%s* - %s%s\n", GREEN_CODE,
				(data())->p_index->str, flag_name((data())->p_index->flag),
				RESET_CODE);
		(data())->p_index = (data())->p_index->next;
	}
}
