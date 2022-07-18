/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:40 by jchene            #+#    #+#             */
/*   Updated: 2022/07/18 16:38:47 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Fill struc with data, at start of function, cursor is on first word of block
int	fill_e_struc(t_exec *struc, char **envp)
{
	if (!get_args((data())->p_index, struc, envp))
		return (0);
	if (!init_close((data())->p_index, struc))
		return (0);
	if (!get_infiles((data())->p_index, struc))
		return (0);
	if (!get_outfiles((data())->p_index, struc))
		return (0);
	if ((data())->p_index->flag == PIP)
		(data())->p_index = (data())->p_index->next;
	while ((data())->p_index && (data())->p_index->flag != PIP)
		(data())->p_index = (data())->p_index->next;
	return (1);
}

/*int	child_process(int input, int output, char **envp)
{
	int	i;

	fprintf(stderr, "%s[%d]inf: %d ouf: %d cls: %d%s\n", GREEN_CODE, getpid(), (data())->nb_inf, (data())->nb_ouf, (data())->nb_cls, RESET_CODE);
	(void)envp;
	i = -1;
	while (++i < (data())->nb_inf)
	{
		fprintf(stderr, "%s[%d]I Closing '%d' and duping '%d' on it%s\n", GREEN_CODE, getpid(), STDIN_FILENO, struc->infiles[i], RESET_CODE);
		dup2(input, STDIN_FILENO);
	}
	i = -1;
	while (++i < (data())->nb_ouf)
	{
		fprintf(stderr, "%s[%d]O Closing '%d' and duping '%d' on it%s\n", GREEN_CODE, getpid(), STDOUT_FILENO, struc->outfiles[i], RESET_CODE);
		dup2(output, STDOUT_FILENO);
	}
	i = -1;
	while (++i < (data())->nb_cls)
	{
		fprintf(stderr, "%s[%d]C Closing '%d'%s\n", GREEN_CODE, getpid(), struc->to_close[i], RESET_CODE);
		close(struc->to_close[i]);
	}
	fprintf(stderr, "%s[%d]Executing %s%s\n", GREEN_CODE, getpid(), struc->args[0], RESET_CODE);
	if (execve(struc->path, struc->args, envp) < 0)
		perror("msh: execvel");
	exit(free_exec(1));
	return (1);
}*/

int	child_process(t_exec *struc, char **envp)
{
	int	i;

	fprintf(stderr, "%s[%d]inf: %d ouf: %d%s\n", GREEN_CODE, getpid(), struc->input, struc->output, RESET_CODE);
	dup2(struc->input, STDIN_FILENO);
	dup2(struc->output, STDOUT_FILENO);
	fprintf(stderr, "%s[%d]Executing %s%s\n", GREEN_CODE, getpid(), struc->args[0], RESET_CODE);
	if (execve(struc->path, struc->args, envp) < 0)
		perror("msh: execvel");
	exit(free_exec(1));
	return (1);
}

//Returns 1 if a pipe is present at then end of block cursor, 0 otherwise
int	pipe_at_end(t_parsing *cursor)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	while (tmp && tmp->flag != PIP)
		tmp = tmp->next;
	if (tmp && tmp->flag == PIP)
		return (1);
	return (0);
}

int	switch_pipe(void)
{
	if ((data())->old_pipe[P_RD] != -1)
		close((data())->old_pipe[P_RD]);
	if ((data())->new_pipe[P_RD] != -1)
		(data())->old_pipe[P_RD] = (data())->new_pipe[P_RD];
	if ((data())->old_pipe[P_WR] != -1)
		close((data())->old_pipe[P_WR]);
	if ((data())->new_pipe[P_WR] != -1)
		(data())->old_pipe[P_WR] = (data())->new_pipe[P_WR];
	if (pipe_at_end((data())->p_index))
		if (pipe((data())->new_pipe) < 0)
			return (0);
	return (1);
}

int	start_exec(char **envp)
{
	int	i;

	fprintf(stderr, "%sHello, i'm parent %d%s\n", YELLOW_CODE, getpid(), RESET_CODE);
	if (!nb_cmds(1))
		return (1);
	if (!init_heredocs())
		return (0);
	i = -1;
	(data())->p_index = (data())->p_start;
	while (++i < nb_cmds(0))
	{
		if (!init_exec())
			return (0);
		if (!switch_pipe())
			return (0);
		if (!fill_e_struc((data())->exec_struc, envp))
			return (0);
		(data())->child_ids[i] = fork();
		if ((data())->child_ids[i] < 0)
			return (iperror("minishell: fork failed", 0));
		if (!(data())->child_ids[i])
			if (child_process((data())->exec_struc, envp) < 0)
				return (0);
		fprintf(stderr, "%sChild[%d] %d born%s\n", YELLOW_CODE, i, (data())->child_ids[i], RESET_CODE);
		free_exec(1);
	}
	return (free_exec(1));
}
