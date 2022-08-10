/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:01:27 by jchene            #+#    #+#             */
/*   Updated: 2022/08/09 17:16:13 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	bad_next_token(t_parsing *tmp, char *wrong_char, int ret)
{
	if (tmp->next->flag == PIP)
		fill_char(wrong_char, '|', 0);
	else if (tmp->next->flag == INF)
		fill_char(wrong_char, '<', 0);
	else if (tmp->next->flag == ROF)
		fill_char(wrong_char, '>', 0);
	else if (tmp->next->flag == HRD && !(wrong_char[0]))
	{
		fill_char(&wrong_char[0], '<', 0);
		fill_char(&wrong_char[1], '<', 0);
	}
	else if (tmp->next->flag == AOF && !(wrong_char[0]))
	{
		fill_char(&wrong_char[0], '>', 0);
		fill_char(&wrong_char[1], '>', 0);
	}
	return (ret);
}

int	check_simple_redir(t_parsing *tmp, char *wrong_char)
{
	char	c;

	c = itern((tmp->flag == INF), '<', '>');
	if (tmp->str[1])
	{
		wrong_char[0] = tmp->str[1];
		if (tmp->str[2] && tmp->str[2] == tmp->str[1])
			wrong_char[1] = tmp->str[2];
		return (INV);
	}
	if (!tmp->next)
		return (fill_char(wrong_char, '\n', INV));
	if (tmp->next->flag != FLN)
		return (bad_next_token(tmp, wrong_char, INV));
	return (itern((c == '<'), INF, ROF));
}

int	check_double_redir(t_parsing *tmp, char *wrong_char)
{
	char	c;

	c = itern((tmp->flag == HRD), '<', '>');
	if (tmp->str[2])
	{
		wrong_char[0] = tmp->str[2];
		if (tmp->str[3] && tmp->str[3] == tmp->str[2])
			wrong_char[1] = tmp->str[3];
		return (INV);
	}
	if (!tmp->next)
		return (fill_char(wrong_char, '\n', INV));
	if ((c == '<' && tmp->next->flag != HDL)
		|| (c == '>' && tmp->next->flag != FLN))
		return (bad_next_token(tmp, wrong_char, INV));
	return (itern((c == '<'), HRD, AOF));
}

int	check_pipe(t_parsing *tmp, char *wrong_char)
{
	if (tmp->str[1])
		return (fill_char(wrong_char, '|', INV));
	if (!tmp->prev)
		return (fill_char(wrong_char, '|', INV));
	if (!tmp->next)
		return (fill_char(wrong_char, '\n', INV));
	if (tmp->next && tmp->next->flag == PIP)
		return (fill_char(wrong_char, '|', INV));
	return (PIP);
}

void	check_symbols(char *wrong_char)
{
	t_parsing	*tmp;

	tmp = (data())->p_start;
	while (tmp)
	{
		if (tmp->flag == INF || tmp->flag == ROF)
			tmp->flag = check_simple_redir(tmp, wrong_char);
		else if (tmp->flag == HRD || tmp->flag == AOF)
			tmp->flag = check_double_redir(tmp, wrong_char);
		else if (tmp->flag == PIP)
			tmp->flag = check_pipe(tmp, wrong_char);
		if (tmp->flag == INV)
			break ;
		tmp = tmp->next;
	}
}
