/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:01:27 by jchene            #+#    #+#             */
/*   Updated: 2022/07/12 14:18:23 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	next_bad_token(t_parsing *tmp, char *wrong_char, int ret)
{
	if (tmp->next->flag == PIP)
		fill_char(&wrong_char[0], '|', 0);
	else if (tmp->next->flag == INF)
		fill_char(&wrong_char[0], '<', 0);
	else if (tmp->next->flag == ROF)
		fill_char(&wrong_char[0], '>', 0);
	else if (tmp->next->flag == HRD && !(wrong_char[0]))
	{
		fill_char(&wrong_char[0], '<', 1);
		fill_char(&wrong_char[1], '<', 1);
	}
	else if (tmp->next->flag == AOF && !(wrong_char[0]))
	{
		fill_char(&wrong_char[0], '>', 1);
		fill_char(&wrong_char[1], '>', 1);
	}
	return (ret);
}

int	check_simple_redir(t_parsing *tmp, char *wrong_char)
{
	int		i;
	char	c;

	i = 0;
	c = itern((tmp->flag == INF), '<', '>');
	while (ft_isdigit(tmp->str[i]))
		i++;
	if (tmp->str[i + 1])
	{
		wrong_char[0] = tmp->str[i + 1];
		if (tmp->str[i + 2] && tmp->str[i + 2] == tmp->str[i + 1])
			wrong_char[1] = tmp->str[i + 2];
		return (INV);
	}
	if (!tmp->next)
		return (fill_char(&wrong_char[0], '\n', INV));
	if (tmp->next->flag != FLN)
		return (next_bad_token(tmp, &wrong_char[0], INV));
	return (itern((c == '<'), INF, ROF));
}

int	check_double_redir(t_parsing *tmp, char *wrong_char)
{
	int		i;
	char	c;

	i = 0;
	c = itern((tmp->flag == HRD), '<', '>');
	while (ft_isdigit(tmp->str[i]))
		i++;
	i++;
	if (tmp->str[i + 1])
	{
		wrong_char[0] = tmp->str[i + 1];
		if (tmp->str[i + 2] && tmp->str[i + 2] == tmp->str[i + 1])
			wrong_char[1] = tmp->str[i + 2];
		return (INV);
	}
	if (!tmp->next)
		return (fill_char(&wrong_char[0], '\n', INV));
	if ((c == '<' && tmp->next->flag != HDL)
		|| (c == '>' && tmp->next->flag != FLN))
		return (next_bad_token(tmp, &wrong_char[0], INV));
	return (itern((c == '<'), HRD, AOF));
}

int	check_pipe(t_parsing *tmp, char *wrong_char)
{
	if (tmp->str[1])
		return (fill_char(wrong_char, '|', INV));
	if (!tmp->prev)
		return (fill_char(&wrong_char[0], '|', INV));
	if (!tmp->next)
		return (fill_char(&wrong_char[0], '\n', INV));
	if (tmp->next->flag == PIP)
		return (fill_char(&wrong_char[0], '|', INV));
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
		tmp = tmp->next;
	}
}
