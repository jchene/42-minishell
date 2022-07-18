/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:16:30 by jchene            #+#    #+#             */
/*   Updated: 2022/07/15 19:30:59 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	close_exec(t_exec *struc)
{
	int	i;

	i = -1;
	while (++i < (data())->nb_inf)
	{
		fprintf(stderr, "%s[%d]*Closing %d%s\n", YELLOW_CODE, getpid(), struc->infiles[i], RESET_CODE);
		close(struc->infiles[i]);
	}
	i = -1;
	while (++i < (data())->nb_ouf)
	{
		fprintf(stderr, "%s[%d]/Closing %d%s\n", YELLOW_CODE, getpid(), struc->outfiles[i], RESET_CODE);
		close(struc->outfiles[i]);
	}
	return (0);
}
