/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:09:47 by jchene            #+#    #+#             */
/*   Updated: 2022/08/13 18:11:06 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	child_exec(t_exec *struc, char **envp)
{
	if (struc->path)
	{
		if (execve(struc->path, struc->args, envp) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(struc->path, 2);
			ft_putstr_fd(": ", 2);
			perror("");
		}
	}
}

int	child_process(t_exec *struc, char **envp)
{
	(data())->in_child++;
	if (struc->input >= 0 && dup2(struc->input, STDIN_FILENO) < 0
		&& exit_exec(1))
		exit(exit_properly((data())->exit_code));
	if (struc->output >= 0 && dup2(struc->output, STDOUT_FILENO) < 0
		&& exit_exec(1))
		exit(exit_properly((data())->exit_code));
	if ((!fd_update(&struc->to_close[P_RD], -1)
			|| !fd_update(&struc->to_close[P_WR], -1)) && exit_exec(1))
		exit(exit_properly((data())->exit_code));
	if ((!fd_update(&struc->out_pipe[P_RD], -1)
			|| !fd_update(&struc->out_pipe[P_WR], -1)) && exit_exec(1))
		exit(exit_properly((data())->exit_code));
	if (is_builtin(struc->path))
		return (exec_builtin(struc));
	child_exec(struc, envp);
	exit_exec(1);
	exit(exit_properly(1));
	return (0);
}
