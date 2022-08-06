/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:29 by jchene            #+#    #+#             */
/*   Updated: 2022/08/06 15:39:05 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_parsing	*new_line(char *src)
{
	t_parsing	*dst;

	dst = malloc(sizeof(t_parsing));
	if (!dst)
	{
		free((data())->line);
		return (NULL);
	}
	dst->next = NULL;
	dst->str = ft_strdup(src);
	if (!dst->str)
	{
		free(dst);
		free((data())->line);
		return (NULL);
	}
	free((data())->line);
	return (dst);
}

int	get_new_line(int ret, char *line, int size)
{
	int	exit_ret;

	if (pipe((data())->temp_pipe) < 0)
		return (0);
	(data())->temp_pid = fork();
	if ((data())->temp_pid < 0)
		return (0);
	if (!(data())->temp_pid)
	{
		close((data())->temp_pipe[P_RD]);
		(data())->in_hrd = 1;
		line = readline("> ");
		ft_putstr_fd(line, (data())->temp_pipe[P_WR]);
		close((data())->temp_pipe[P_WR]);
		free(line);
		exit(0);
	}
	close((data())->temp_pipe[P_WR]);
	waitpid((data())->temp_pid, &exit_ret, 0);
	exit_ret = WEXITSTATUS(exit_ret);
	while (ret > 0 && !exit_ret)
	{
		size *= 2;
		line = malloc(sizeof(char) * size);
		if (!line)
			return (0);
		ret = read((data())->temp_pipe[P_RD], &line, size);
		if (ret < 0)
			return (0);
		if (ret)
			free(line);
	}
	close((data())->temp_pipe[P_RD]);
	if (ret)
	{
		fprintf(stderr, "NULL\n");
		line = NULL;
	}
	if ((data())->line)
		free((data())->line);
	(data())->line = NULL;
	if (line)
	{
		(data())->line = ft_strdup(line);
		free(line);
	}
	return (1);
}

char	*get_lines(t_parsing *lines, t_parsing *index)
{
	if (!get_new_line(1, NULL, 0))
		return (NULL);
	while ((data())->line && (!(data())->line[0]
			|| !ft_strcmp((data())->p_index->next->str, (data())->line)))
	{
		if (!lines)
		{
			lines = new_line((data())->line);
			if (!lines)
				return (NULL);
			index = lines;
			if (!get_new_line(1, NULL, 0))
				return (NULL);
			continue ;
		}
		index->next = new_line((data())->line);
		if (!index->next && free_p_struct(&lines))
			return (NULL);
		index = index->next;
		if (!get_new_line(1, NULL, 0))
			return (NULL);
	}
	return (end_of_hrd(lines));
}

int	new_heredoc(void)
{
	if (!(data())->he_start)
	{
		fprintf(stderr, "NO_HST\n");
		(data())->he_start = malloc(sizeof(t_parsing));
		if (!(data())->he_start)
			return (0);
		(data())->he_start->next = NULL;
		(data())->he_start->str = get_lines(NULL, NULL);
		if (!(data())->he_start->str)
			return (0);
	}
	else
	{
		(data())->he_index = (data())->he_start;
		while ((data())->he_index->next)
			(data())->he_index = (data())->he_index->next;
		(data())->he_index->next = malloc(sizeof(t_parsing));
		if (!(data())->he_index->next)
			return (0);
		(data())->he_index->next->next = NULL;
		(data())->he_index->next->str = get_lines(NULL, NULL);
		if (!(data())->he_index->next->str)
			return (0);
	}
	return (1);
}

int	init_heredocs(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		if ((data())->p_index->flag == HRD)
			if (!new_heredoc())
				return (0);
		(data())->p_index = (data())->p_index->next;
	}
	if ((data())->he_start)
		rm_dollars((data())->he_start, NULL, 1);
	return (1);
}
