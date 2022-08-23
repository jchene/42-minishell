/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 00:11:09 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 19:52:38 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	fill_that_line(int i)
{
	if (!(data())->line_start->c && !free_that_line())
		return (1);
	(data())->line_index = (data())->line_start;
	while ((data())->line_index && ++i)
		(data())->line_index = (data())->line_index->next;
	(data())->line = malloc(sizeof(char) * i + 1);
	if (!(data())->line)
		return (free_that_line());
	(data())->line[i] = '\0';
	i = -1;
	(data())->line_index = (data())->line_start;
	while ((data())->line_index && ++i >= 0)
	{
		(data())->line[i] = (data())->line_index->c;
		(data())->line_index = (data())->line_index->next;
	}
	free_that_line();
	return (1);
}

int	add_line(char c)
{
	(data())->line_index->next = malloc(sizeof(t_line));
	if (!(data())->line_index->next)
		return (0);
	(data())->line_index = (data())->line_index->next;
	(data())->line_index->c = c;
	(data())->line_index->next = NULL;
	return (1);
}

int	new_line(int ret, char c, int hrd_ret)
{
	while (ret)
	{
		ret = read((data())->temp_pipe[P_RD], &c, 1);
		if (ret < 0)
			return (0);
		if (!ret && hrd_ret != 4)
			c = '\0';
		if (!ret && hrd_ret == 4)
			c = '\n';
		if (!(data())->line_start)
		{
			(data())->line_start = malloc(sizeof(t_line));
			if (!(data())->line_start)
				return (0);
			(data())->line_start->c = c;
			(data())->line_start->next = NULL;
			(data())->line_index = (data())->line_start;
			continue ;
		}
		if (!add_line(c))
			return (free_that_line());
	}
	return (fill_that_line(0));
}

void	hrd_process(char *line)
{
	int	ret;

	ret = 0;
	(data())->in_hrd = 1;
	rl_clear_history();
	close((data())->temp_pipe[P_RD]);
	line = readline("> ");
	if (line)
	{
		if (!line[0])
			ret = 4;
		ft_putstr_fd(line, (data())->temp_pipe[P_WR]);
		free(line);
	}
	close((data())->temp_pipe[P_WR]);
	free_p_struct(&(data())->lines);
	exit(exit_properly(ret));
}

int	get_new_line(int ret)
{
	(data())->line_start = NULL;
	if (pipe((data())->temp_pipe) < 0)
		return (0);
	(data())->temp_pid = fork();
	if ((data())->temp_pid < 0)
		return (0);
	if (!(data())->temp_pid)
		hrd_process(NULL);
	close((data())->temp_pipe[P_WR]);
	waitpid((data())->temp_pid, &ret, 0);
	(data())->temp_pid = -1;
	ret = WEXITSTATUS(ret);
	if ((!ret || ret == 4) && !new_line(1, 0, ret)
		&& fd_update(&(data())->temp_pipe[P_RD], 0) >= 0)
		return (0);
	close((data())->temp_pipe[P_RD]);
	if (ret == 130)
		return (-1);
	return (1);
}
