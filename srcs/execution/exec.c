/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:40 by jchene            #+#    #+#             */
/*   Updated: 2022/08/05 19:38:41 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	child_process(t_exec *struc, char **envp)
{
	if (struc->input >= 0)
		if (dup2(struc->input, STDIN_FILENO) < 0)
			return (exit_exec(iperror("minishell: dup2", 0)));
	if (struc->output >= 0)
		if (dup2(struc->output, STDOUT_FILENO) < 0)
			return (exit_exec(iperror("minishell: dup2", 0)));
	if (!fd_update(&struc->to_close[P_RD], -1)
		|| !fd_update(&struc->to_close[P_WR], -1))
		return (exit_exec(0));
	if (!fd_update(&struc->out_pipe[P_RD], -1)
		|| !fd_update(&struc->out_pipe[P_WR], -1))
		return (exit_exec(0));
	if (is_builtin(struc->path))
		return (exec_builtin(struc));
	if (execve(struc->path, struc->args, envp) < 0)
		perror("minishell: execve");
	exit(exit_exec(1));
	return (1);
}

int	launch_child(int i, char **envp)
{
	int	temp;

	if ((data())->skip_exec)
	{
		(data())->child_ids[i] = -1;
		return (1);
	}
	temp = is_builtin((data())->exec_struc->path);
	if (temp)
		apply_builtin((data())->exec_struc, temp, 0);
	(data())->child_ids[i] = fork();
	if ((data())->child_ids[i] < 0)
		return (iperror("minishell: fork", 0));
	if (!(data())->child_ids[i])
		if (!child_process((data())->exec_struc, envp))
			return (0);
	return (1);
}

//Fill struc with data, at start of function, cursor is on first word of block
int	fill_e_struc(t_exec *struc, char **envp)
{
	if (!get_args((data())->p_index, struc, envp))
		return (0);
	if ((data())->skip_exec)
		return (1);
	if (!get_infiles((data())->p_index, struc))
		return (0);
	if ((data())->skip_exec)
		return (1);
	if (!get_outfiles((data())->p_index, struc))
		return (0);
	if ((data())->skip_exec)
		return (1);
	if ((data())->p_index->flag == PIP)
		(data())->p_index = (data())->p_index->next;
	while ((data())->p_index && (data())->p_index->flag != PIP)
		(data())->p_index = (data())->p_index->next;
	return (1);
}

int	switch_pipe(void)
{
	if (!fd_update(&(data())->old_pipe[P_RD], -1))
		return (0);
	if ((data())->new_pipe[P_RD] != -1)
		(data())->old_pipe[P_RD] = (data())->new_pipe[P_RD];
	if (!fd_update(&(data())->old_pipe[P_WR], -1))
		return (0);
	if ((data())->new_pipe[P_WR] != -1)
		(data())->old_pipe[P_WR] = (data())->new_pipe[P_WR];
	if (pipe_at_end((data())->p_index))
	{
		if (pipe((data())->new_pipe) < 0)
			return (iperror("minishell: pipe", 0));
	}
	return (1);
}

int	start_exec(char **envp)
{
	int	i;

	if (!nb_cmds(UP))
		return (1);
	if (!init_heredocs())
		return (0);
	if (!first_init())
		return (0);
	i = -1;
	(data())->p_index = (data())->p_start;
	while (++i < nb_cmds(NO_UP))
	{
		if (!init_exec())
			return (exit_exec(0));
		if (!switch_pipe())
			return (exit_exec(0));
		if (!fill_e_struc((data())->exec_struc, envp))
			return (exit_exec(0));
		if (!launch_child(i, envp))
			return (exit_exec(0));
	}
	return (exit_exec(1));
}
