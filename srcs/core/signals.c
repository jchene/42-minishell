/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:34 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 16:56:47 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (!(data())->in_hrd && !(data())->child_ids
		&& !(data())->in_child && (data())->temp_pid < 0)
	{
		fprintf(stderr, "1\n");
		(data())->exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		if (!(data())->passif_mode)
			rl_redisplay();
	}
	else if ((data())->in_hrd)
	{
		fprintf(stderr, "2\n");
		write(1, "\n", 1);
		(data())->passif_mode = 1;
		close((data())->temp_pipe[P_WR]);
		free_p_struct(&(data())->lines);
		exit(exit_properly(130));
	}
	else if ((data())->in_child)
	{
		fprintf(stderr, "3\n");
		exit_exec(0);
		exit(exit_properly(130));
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if ((data())->passif_mode)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	else
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

int	ft_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_bs);
	return (1);
}
