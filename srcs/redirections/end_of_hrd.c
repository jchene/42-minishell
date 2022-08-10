/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_hrd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:52:59 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/10 12:39:58 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	join_lines(t_parsing *index, int i, int j, char **str)
{
	while ((data())->lines)
	{
		index = (data())->lines;
		(data())->lines = (data())->lines->next;
		j = -1;
		if (index->str)
		{
			while (index->str[++j])
				(*str)[i + j] = index->str[j];
			if ((*str)[i + j - 1] != '\n')
			{
				(*str)[i + j] = '\n';
				i += j + 1;
			}
			else
				i += j;
			free(index->str);
		}
		free(index);
	}
	(*str)[i] = '\0';
}

char	*strlcat_lines(t_parsing *index, int i, char *str)
{
	while (index)
	{
		if (index->str[0] == '\n')
			i++;
		else
			i += ft_strlen(index->str) + 1;
		index = index->next;
	}
	str = malloc(sizeof(char) * i + 1);
	if (!str && free_p_struct(&(data())->lines))
		return (NULL);
	join_lines(NULL, 0, 0, &str);
	return (str);
}

int	end_of_hrd(char **str, int ret)
{
	if ((!ret || ret == -1) && free_p_struct(&(data())->lines))
	{
		if ((data())->line)
			free((data())->line);
		(data())->line = NULL;
		return (ret);
	}
	if (!(data())->line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd((data())->lines_executed, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd((data())->p_index->next->str, 2);
		ft_putstr_fd("')\n", 2);
	}
	else
		free((data())->line);
	(data())->line = NULL;
	*str = strlcat_lines((data())->lines, 0, NULL);
	return (ret);
}
