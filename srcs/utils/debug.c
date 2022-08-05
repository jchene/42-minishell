/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:33:05 by jchene            #+#    #+#             */
/*   Updated: 2022/08/03 14:54:39 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

const char	*flag_name(int flag)
{
	if (flag == INF)
		return ("INFILE");
	else if (flag == HRD)
		return ("HEREDOC");
	else if (flag == ROF)
		return ("REPLACE FILE");
	else if (flag == AOF)
		return ("APPEND FILE");
	else if (flag == FLN)
		return ("FILENAME");
	else if (flag == HDL)
		return ("HEREDOC DELIM");
	else if (flag == CMD)
		return ("COMMAND");
	else if (flag == ARG)
		return ("ARGUMENT");
	else if (flag == PIP)
		return ("PIPE");
	else if (flag == NWL)
		return ("NEWLINE");
	else if (flag == INV)
		return ("INVALID");
	return (NULL);
}

void	display_list(void)
{
	(data())->p_index = (data())->p_start;
	while ((data())->p_index)
	{
		if ((data())->p_index->flag == INV)
			fprintf(stderr, "%s*%s* - %s%s\n", RED_CODE,
				(data())->p_index->str, flag_name((data())->p_index->flag),
				RESET_CODE);
		else
			fprintf(stderr, "%s*%s* - %s%s\n", GREEN_CODE,
				(data())->p_index->str, flag_name((data())->p_index->flag),
				RESET_CODE);
		(data())->p_index = (data())->p_index->next;
	}
}

//Display all heredocs
void	display_heredocs(void)
{
	t_parsing	*tmp;
	int			i;

	tmp = (data())->he_start;
	i = 1;
	while (tmp)
	{
		printf("Heredoc #%d\n", i);
		printf("-------------\n");
		printf("%s		---	%s\n", tmp->str, flag_name(tmp->flag));
		printf("-----end-----\n");
		tmp = tmp->next;
		i++;
	}
}
