/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:17:58 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/25 19:17:55 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	something_behind_redir(int backup)
{
	if (ft_isdigit((data())->line[(data())->j - 1]))
	{
		while ((data())->j > 0 && ft_isdigit((data())->line[(data())->j - 1]))
			(data())->j--;
		if ((data())->j == (data())->i)
		{
			(data())->j = backup;
			return (1);
		}
	}
	if (!fill_p_struct_str())
		return (0);
	(data())->i = (data())->j;
	if (!new_p_struct_member())
		return (0);
	while (ft_isdigit((data())->line[(data())->j]))
		(data())->j++;
	return (1);
}

int	redir_finded(void)
{
	if ((data())->j != (data())->i)
		if (!something_behind_redir((data())->j))
			return (0);
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
	while ((data())->line[(data())->j]
		&& (data())->line[(data())->j] != ' ')
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
		if ((data())->line[(data())->j] && (data())->line[(data())->j] != ' ')
			(data())->j++;
	}
	return (1);
}

int	split_line(void)
{
	(data())->i = 0;
	while ((data())->line && (data())->line[(data())->i])
	{
		if ((data())->line[(data())->i] != ' ')
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
		if ((data())->line[(data())->i] && (data())->line[(data())->i] == ' ')
			(data())->i++;
	}
	if ((data())->line)
		free((data())->line);
	(data())->line = NULL;
	return (1);
}
