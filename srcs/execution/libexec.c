/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:01:53 by jchene            #+#    #+#             */
/*   Updated: 2022/07/15 19:39:17 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//If flag is 0, returns number of commands in pipeline, reset ret otherwise
int	nb_cmds(int reset)
{
	static int	ret = -1;
	t_parsing	*tmp;

	if (reset)
		ret = -1;
	if (ret == -1)
	{
		tmp = (data())->p_start;
		ret = 0;
		while (tmp)
		{
			if (tmp->flag == CMD)
				ret++;
			tmp = tmp->next;
		}
	}
	return (ret);
}

//Wait for all childs to terminate
void	wait_all(void)
{
	int	i;

	i = -1;
	fprintf(stderr, "%sWaiting for all%s\n", YELLOW_CODE, RESET_CODE);
	while (++i < nb_cmds(0))
	{
		fprintf(stderr, "%sWaiting for [%d]: %d%s\n", YELLOW_CODE, i, (data())->child_ids[i], RESET_CODE);
		waitpid((data())->child_ids[i], NULL, 0);
		fprintf(stderr, "%sChild[%d] done%s\n", YELLOW_CODE, (data())->child_ids[i], RESET_CODE);
	}
	fprintf(stderr, "%sAll childs done.%s\n", YELLOW_CODE, RESET_CODE);
}
