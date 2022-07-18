/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:50:05 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/15 18:44:36 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	some_more_free(void)
{
	if ((data())->exec_struc)
		free(data()->exec_struc);
	if ((data())->p_start)
		free_p_struct();
	if ((data())->exp_start)
		free_exp_struct();
	if ((data())->line)
		free((data())->line);
	if ((data())->temp)
		free((data())->temp);
	if ((data())->child_ids)
		free((data())->child_ids);
}

int	exit_properly(int ret)
{
	rl_clear_history();
	if ((data())->path)
	{
		(data())->i = -1;
		while ((data())->path[++(data())->i])
			free((data())->path[(data())->i]);
		free((data())->path);
	}
	if ((data())->h_start)
		if (!create_history_file())
			perror("Create History Error");
	some_more_free();
	/*if (ret == -1)
		perror("Error");*/
	return (ret);
}
