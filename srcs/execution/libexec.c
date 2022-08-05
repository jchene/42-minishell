/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:01:53 by jchene            #+#    #+#             */
/*   Updated: 2022/08/05 09:34:06 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Returns number of commands in pipeline. Use flags UP or NO_UP to update or not
int	nb_cmds(int flag)
{
	static int	ret = -1;
	t_parsing	*tmp;

	if (flag)
		ret = -1;
	if (ret == -1)
	{
		tmp = (data())->p_start;
		ret = 0;
		while (tmp)
		{
			if (tmp->flag == CMD)
				ret++;
			tmp = tmp->next;
		}
	}
	return (ret);
}

//Wait for all childs to terminate
int	wait_all(void)
{
	int	i;
	int	temp;

	i = -1;
	while (++i < nb_cmds(NO_UP))
		if ((data())->child_ids[i] != -1)
			if (waitpid((data())->child_ids[i], &temp, 0) < 0)
				return (iperror("minishell: waitpid", 0));
	if (!(data())->got_from_builtsin)
		(data())->exit_code = WEXITSTATUS((data())->exit_code);
	return (1);
}

//Returns 1 if a pipe is present at then end of block cursor, 0 otherwise
int	pipe_at_end(t_parsing *cursor)
{
	t_parsing	*tmp;

	tmp = cursor;
	if (tmp && tmp->flag == PIP)
		tmp = tmp->next;
	while (tmp && tmp->flag != PIP)
		tmp = tmp->next;
	if (tmp)
		return (1);
	return (0);
}

//Closes securely fd at fd_ptr and puts value into ft_ptr
int	fd_update(int *fd_ptr, int value)
{
	if (*fd_ptr >= 0)
	{
		if (close(*fd_ptr) < 0)
			return (iperror("minishell: close", 0));
	}
	*fd_ptr = value;
	return (1);
}
