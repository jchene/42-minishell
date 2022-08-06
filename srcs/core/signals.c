/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:49:34 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 17:16:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (!(data())->in_hrd)
	{
		rl_on_new_line();
		rl_replace_line ("", 0);
		if (!(data())->passif_mode)
			rl_redisplay();
	}
	else if (!(data())->temp_pid)
	{
		close((data())->temp_pipe[P_WR]);
		exit(3);
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
}

int	ft_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_bs);
	return (1);
}
