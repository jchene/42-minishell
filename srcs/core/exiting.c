/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:50:05 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 16:08:27 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	some_more_free(void)
{
	if ((data())->exec_struc)
		free(data()->exec_struc);
	if ((data())->line)
		free((data())->line);
	if ((data())->temp)
		free((data())->temp);
	if ((data())->child_ids)
		free((data())->child_ids);
	if ((data())->envp)
		free_str_tab2((data())->envp);
	if ((data())->p_start)
		free_p_struct(&(data())->p_start);
	if ((data())->exp_start)
		free_exp_struct();
	if ((data())->he_start)
		free_p_struct(&(data())->he_start);
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
	{
		if (!(data())->in_child)
		{	
			if (!create_history_file())
				perror("Error while creating history file ");
		}
		else
			ft_clear_history();
	}
	some_more_free();
	return (ret);
}
