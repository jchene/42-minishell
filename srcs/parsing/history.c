/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:34:34 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/02 03:45:54 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_clear_history(void)
{
	t_history	*temp;

	(data())->h_index = (data())->h_start;
	while ((data())->h_index)
	{
		temp = (data())->h_index;
		(data())->h_index = (data())->h_index->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	return (0);
}

int	create_history_file(void)
{
	int			fd;
	t_history	*temp;

	fd = open(".bash_history", O_CREAT | O_APPEND | O_RDWR, 0600);
	if (fd == -1)
		return (ft_clear_history());
	(data())->h_index = (data())->h_start;
	while ((data())->h_index)
	{
		write(fd, (data())->h_index->str, ft_strlen((data())->h_index->str));
		write(fd, "\n", 1);
		temp = (data())->h_index;
		(data())->h_index = (data())->h_index->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	if (close(fd) < 0)
		return (0);
	return (1);
}

int	add_in_history(char *str)
{
	(data())->h_index = (data())->h_start;
	while ((data())->h_index->next)
		(data())->h_index = (data())->h_index->next;
	(data())->h_index->next = malloc(sizeof(t_history));
	if (!(data())->h_index->next)
		return (0);
	(data())->h_index->next->prev = (data())->h_index;
	(data())->h_index->next->next = NULL;
	(data())->h_index->next->str = ft_strdup(str);
	if (!(data())->h_index->next->str)
		return (0);
	return (1);
}

int	init_history(char *str)
{
	(data())->h_start = malloc(sizeof(t_history));
	if (!(data())->h_start)
		return (0);
	(data())->h_start->next = NULL;
	(data())->h_start->prev = NULL;
	(data())->h_start->str = ft_strdup(str);
	if (!(data())->h_start->str)
	{
		free((data())->h_start);
		(data())->h_start = NULL;
		return (0);
	}
	return (1);
}
