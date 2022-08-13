/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:34 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 01:32:19 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ctrl_c(int sig)
{
	(void)sig;
	if (!(data())->child_ids && (data())->temp_pid < 0
		&& !(data())->passif_mode)
	{
		(data())->exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
	else if ((data())->in_hrd)
	{
		write(1, "\n", 1);
		close((data())->temp_pipe[P_WR]);
		free_p_struct(&(data())->lines);
		exit(exit_properly(130));
	}
	else
	{
		write(1, "\n", 1);
		(data())->exit_code = 130;
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if ((data())->passif_mode)
	{
		(data())->exit_code = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

int	ft_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_bs);
	return (1);
}
