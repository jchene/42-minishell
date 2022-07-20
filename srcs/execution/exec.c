/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:40 by jchene            #+#    #+#             */
/*   Updated: 2022/07/21 00:27:36 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	child_process(t_exec *struc, char **envp)
{
	//fprintf(stderr, "%s[%d]inf: %d ouf: %d%s\n", GREEN_CODE, getpid(), struc->input, struc->output, RESET_CODE);
	if (struc->input >= 0)
		if (dup2(struc->input, STDIN_FILENO) < 0)
			return (iperror("minishell: dup2", 0));
	if (struc->output >= 0)
		if (dup2(struc->output, STDOUT_FILENO) < 0)
			return (iperror("minishell: dup2", 0));
	if (struc->to_close[0] >= 0)
		if (close(struc->to_close[0]) < 0)
			return (iperror("minishell: close4", 0));
	if (struc->to_close[1] >= 0)
		if (close(struc->to_close[1]) < 0)
			return (iperror("minishell: close5", 0));
	//fprintf(stderr, "%s[%d]Executing %s%s\n", GREEN_CODE, getpid(), struc->args[0], RESET_CODE);
	if (!access(struc->path, F_OK))
		if (execve(struc->path, struc->args, envp) < 0)
			perror("minishell: execve");
	exit(free_exec(1));
	return (1);
}

int	switch_pipe(void)
{
	if ((data())->old_pipe[P_RD] != -1)
		if (close((data())->old_pipe[P_RD]) < 0)
			return (iperror("minishell: close1", 0));
	if ((data())->new_pipe[P_RD] != -1)
		(data())->old_pipe[P_RD] = (data())->new_pipe[P_RD];
	if ((data())->old_pipe[P_WR] != -1)
		if (close((data())->old_pipe[P_WR]))
			return (iperror("minishell: close2", 0));
	if ((data())->new_pipe[P_WR] != -1)
		(data())->old_pipe[P_WR] = (data())->new_pipe[P_WR];
	if (pipe_at_end((data())->p_index))
		if (pipe((data())->new_pipe) < 0)
			return (iperror("minishell: pipe", 0));
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

int	launch_child(int i, char **envp)
{
	if ((data())->skip_exec)
	{
		(data())->child_ids[i] = -1;
		return (1);
	}
	(data())->child_ids[i] = fork();
	if ((data())->child_ids[i] < 0)
		return (iperror("minishell: fork", 0));
	if (!(data())->child_ids[i])
		if (!child_process((data())->exec_struc, envp))
			return (0);
	//fprintf(stderr, "%sChild[%d] %d born%s\n", YELLOW_CODE, i, (data())->child_ids[i], RESET_CODE);
	return (1);
}

int	start_exec(char **envp)
{
	int	i;

	//fprintf(stderr, "%sHello, i'm parent %d%s\n", YELLOW_CODE, getpid(), RESET_CODE);
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
			return (0);
		if (!switch_pipe())
			return (0);
		if (!fill_e_struc((data())->exec_struc, envp))
			return (0);
		if (!launch_child(i, envp))
			return (0);
	}
	return (free_exec(1));
}
