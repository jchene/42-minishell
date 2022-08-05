/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:58 by jchene            #+#    #+#             */
/*   Updated: 2022/08/03 14:40:19 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Counts a specific flag in the pipe block
int	count_block_flags(t_parsing *tmp, int flag)
{
	int			ret;

	ret = 0;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	while (tmp && tmp->flag != PIP)
	{
		if (tmp->flag == flag)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

//Counts a specific flag in the pipeline
int	count_list_flags(int flag)
{
	int			ret;
	t_parsing	*tmp;

	ret = 0;
	tmp = (data())->p_start;
	while (tmp)
	{
		if (tmp->flag == flag)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}
