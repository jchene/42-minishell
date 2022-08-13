/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 01:22:53 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/13 17:50:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

const char	*get_err_str(int err_code)
{
	if (err_code == ER_CMD_PE)
		return ("Permission denied");
	if (err_code == ER_CMD_FO)
		return ("command not found");
	if (err_code == ER_CMD_PA)
		return ("No such file or directory");
	if (err_code == ER_CMD_DI)
		return ("Is a directory");
	return ("Bad error code");
}

unsigned long	display_error(int err_code, char *name, int bash_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)get_err_str(err_code), 2);
	ft_putstr_fd("\n", 2);
	if (err_code > 0)
	{
		(data())->exit_code = bash_code;
		(data())->skip_exec = 1;
	}
	return (0);
}

int	nb_pipes(int flag)
{
	static int	ret = 0;
	t_parsing	*tmp;

	if (flag)
		ret = -1;
	if (ret == -1)
	{
		tmp = (data())->p_start;
		ret = 0;
		while (tmp)
		{
			if (tmp->flag == PIP)
				ret++;
			tmp = tmp->next;
		}
	}
	return (ret + 1);
}
