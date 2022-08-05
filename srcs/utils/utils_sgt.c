/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:50:36 by jchene            #+#    #+#             */
/*   Updated: 2022/08/01 22:05:56 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Return l'addresse de la structure statique data
t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

//Return l'addresse de la statique var (réservée flagging)
int	*seen_cmd(void)
{
	static int	var = 0;

	return (&var);
}

//Return l'addresse de la statique var (réservée parsing)
int	*is_d_quoted(void)
{
	static int	var = 0;

	return (&var);
}

//Return l'addresse de la statique var (réservée parsing)
int	*is_s_quoted(void)
{
	static int	var = 0;

	return (&var);
}
