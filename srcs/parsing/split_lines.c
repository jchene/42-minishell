/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:17:58 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/12 10:52:03 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	redir_finded(void)
{
	if ((data())->j != (data())->i)
	{
		if (!fill_p_struct_str())
			return (0);
		(data())->i = (data())->j;
		if (!new_p_struct_member())
			return (0);
	}
	(data())->j++;
	while ((data())->line[(data())->j] && ((data())->line[(data())->j] == '>'
			|| (data())->line[(data())->j] == '<'))
		(data())->j++;
	return (1);
}

int	pipe_finded(void)
{
	if ((data())->j != (data())->i)
	{
		if (!fill_p_struct_str())
			return (0);
		(data())->i = (data())->j;
		if (!new_p_struct_member())
			return (0);
	}
	(data())->j++;
	while ((data())->line[(data())->j] && ((data())->line[(data())->j] == '|'))
		(data())->j++;
	return (1);
}

int	next_str(int quote)
{
	while ((data())->line[(data())->j] && (data())->line[(data())->j] != ' '
		&& (data())->line[(data())->j] != '\t')
	{
		if ((data())->line[(data())->j] == '|')
			return (pipe_finded());
		if ((data())->line[(data())->j] == '>'
			|| (data())->line[(data())->j] == '<')
			return (redir_finded());
		if ((data())->line[(data())->j] == D_QUOTE
			|| (data())->line[(data())->j] == S_QUOTE)
		{
			quote = (data())->line[(data())->j];
			(data())->j++;
			while ((data())->line[(data())->j]
				&& (data())->line[(data())->j] != quote)
				(data())->j++;
		}
		if ((data())->line[(data())->j] && (data())->line[(data())->j] != ' '
			&& (data())->line[(data())->j] != '\t')
			(data())->j++;
	}
	return (1);
}

int	go_til_space(void)
{
	if ((data())->line[(data())->i] != ' '
		&& (data())->line[(data())->i] != '\t')
	{
		if (!new_p_struct_member())
			return (0);
		(data())->j = (data())->i;
		if (!next_str(0))
			return (0);
		if (!fill_p_struct_str())
			return (0);
		(data())->i = (data())->j;
	}
	if ((data())->line[(data())->i] && ((data())->line[(data())->i] == ' '
			|| (data())->line[(data())->i] == '\t'))
		(data())->i++;
	return (1);
}

int	split_line(void)
{
	(data())->i = 0;
	while ((data())->line && (data())->line[(data())->i])
		go_til_space();
	if (!(data())->p_start && (data())->line
		&& ((data())->line[0] == ' ' || (data())->line[0] == '\t'))
	{
		if (!new_p_struct_member())
			return (0);
		(data())->p_start->str = ft_strdup(" ");
		if (!(data())->p_start->str)
			return (0);
	}
	if ((data())->line)
		free((data())->line);
	(data())->line = NULL;
	return (1);
}
