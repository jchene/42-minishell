/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:27:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/02/04 10:27:26 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	end_of_prompt(void)
{
	if ((data())->child_ids)
	{
		free((data())->child_ids);
		(data())->child_ids = NULL;
	}
	if ((data())->he_start)
		free_p_struct(&(data())->he_start);
	(data())->lines_executed++;
	(data())->he_read = 0;
	(data())->got_from_builtsin = 0;
	return (1);
}

int	new_prompt(int ret)
{
	if ((data())->p_start)
		free_p_struct(&(data())->p_start);
	nb_cmds(UP);
	if (!read_input())
		return (0);
	if (!split_line())
		return (0);
	if (!rm_quotes())
		return (0);
	if (!rm_dollars((data())->p_start, NULL, 0))
		return (0);
	if (!check_input())
		return (end_of_prompt());
	if (!flag_words())
		return (end_of_prompt());
	if (!(data())->p_start)
		return (end_of_prompt());
	ret = start_exec((data())->envp, 0, 0);
	if (!ret)
		return (0);
	if (ret > 0 && !wait_all())
		return (0);
	return (end_of_prompt());
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_signal();
	if (!init_data(envp))
		return (exit_properly(0));
	if (!create_exp_struct())
		return (exit_properly(0));
	while (!(data())->stop)
		if (!new_prompt(0))
			return (exit_properly(0));
	return (exit_properly(data()->exit_code));
}
