/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:39:17 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/08 21:59:38 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_exp_struct(void)
{
	t_export	*temp;

	(data())->exp_index = (data())->exp_start;
	while ((data())->exp_index)
	{
		temp = (data())->exp_index;
		(data())->exp_index = (data())->exp_index->next;
		if (temp == (data())->exp_end)
			(data())->exp_end = NULL;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	(data())->exp_start = NULL;
	(data())->exp_index = (data())->exp_end;
	while ((data())->exp_index)
	{
		temp = (data())->exp_index;
		(data())->exp_index = (data())->exp_index->prev;
		if (temp->str)
			free((temp)->str);
		free(temp);
	}
	(data())->exp_end = NULL;
	return (0);
}

int	free_p_struct(t_parsing **start)
{
	t_parsing	*temp;

	while (*start)
	{
		temp = *start;
		*start = (*start)->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	*start = NULL;
	return (1);
}

int	free_that_line(void)
{
	while ((data())->line_start)
	{
		(data())->line_index = (data())->line_start;
		(data())->line_start = (data())->line_start->next;
		free((data())->line_index);
	}
	return (0);
}
