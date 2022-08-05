/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_hrd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:52:59 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/04 20:58:00 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*return_str(char *str, int i)
{
	if (!i)
		str[i] = '\0';
	else
		str[i - 1] = '\0';
	return (str);
}

char	*strlcat_lines(t_parsing *lines, t_parsing *index, int i, int j)
{
	char	*str;

	while (index)
	{
		i += ft_strlen(index->str) + 1;
		index = index->next;
	}
	str = malloc(sizeof(char) * (i - 1) + 1);
	if (!str && free_p_struct(&lines))
		return (NULL);
	i = 0;
	while (lines)
	{
		index = lines;
		lines = lines->next;
		j = -1;
		while (index->str[++j])
			str[i + j] = index->str[j];
		str[i + j] = '\n';
		i += j + 1;
		free(index->str);
		free(index);
	}
	return (return_str(str, i));
}

char	*end_of_hrd(t_parsing *lines)
{
	if (!(data())->line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd((data())->lines_executed, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd((data())->p_index->next->str, 2);
		ft_putstr_fd("')\n", 2);
	}
	free((data())->line);
	if (!lines)
		return (strlcat_lines(lines, lines, 1, 0));
	return (strlcat_lines(lines, lines, 0, 0));
}
