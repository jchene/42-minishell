/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:05:27 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/11 15:06:25 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*hide_that(void)
{
	char	*str;

	str = ft_strdup("OLDPWD");
	if (!str)
		return (NULL);
	return (str);
}

char	*envp_to_export(char *s, int founded)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	i = 0;
	if (s[0] == '_' && s[1] == '=')
		return (hide_that());
	while (s[i])
		i++;
	str = malloc(sizeof(char) * (i + 2) + 1);
	if (!str)
		return (NULL);
	j = -1;
	k = -1;
	while (i--)
	{
		str[++j] = s[++k];
		if (s[k] == '=' && !founded && ++founded)
			str[++j] = D_QUOTE;
	}
	if (founded)
		str[++j] = D_QUOTE;
	str[++j] = '\0';
	return (str);
}

int	init_data(char **envp)
{
	data();
	(data())->stop = 0;
	(data())->exit_code = 0;
	(data())->got_from_builtsin = 0;
	(data())->line = NULL;
	(data())->lines = NULL;
	(data())->envp = NULL;
	(data())->envp_size = 0;
	(data())->h_start = NULL;
	(data())->p_start = NULL;
	(data())->exp_start = NULL;
	(data())->exp_end = NULL;
	(data())->he_start = NULL;
	(data())->he_read = 0;
	(data())->lines_executed = 1;
	(data())->in_child = 0;
	(data())->passif_mode = 0;
	(data())->in_hrd = 0;
	(data())->temp_pid = -1;
	(data())->child_ids = NULL;
	if (!create_envp(envp))
		return (0);
	return (1);
}
