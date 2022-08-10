/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagging.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:27:28 by jchene            #+#    #+#             */
/*   Updated: 2022/08/09 17:18:35 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//Return 1 si word est une redirection, 0 sinon, inscrit le bon flag dans flag
int	is_redir(char *word, int *flag)
{
	if (word[0] && word[0] == '<'
		&& (!word[1] || (word[1] && word[1] != word[0])))
		return (set_int(flag, INF, 1));
	else if (word[0] && word[0] == '>'
		&& (!word[1] || (word[1] && word[1] != word[0])))
		return (set_int(flag, ROF, 1));
	else if (word[0] == '<' && word[1] && word[1] == '<')
		return (set_int(flag, HRD, 1));
	else if (word[0] == '>' && word[1] && word[1] == '>')
		return (set_int(flag, AOF, 1));
	else
		return (set_int(flag, INV, 0));
}

//Return le flag correspondant au mot du p_index actuel
int	get_flag(void)
{
	int		flag;
	char	*word;

	flag = INV;
	word = (data())->p_index->str;
	if (!word)
		return (INV);
	if (is_redir(word, &flag))
		return (flag);
	else if (word[0] == '|')
	{	
		*(seen_cmd()) = 0;
		return (PIP);
	}
	else if ((data())->p_index->prev && (((data())->p_index->prev->flag == INF)
			|| ((data())->p_index->prev->flag == ROF)
			|| ((data())->p_index->prev->flag == AOF)))
		return (FLN);
	else if ((data())->p_index->prev && (data())->p_index->prev->flag == HRD)
		return (HDL);
	else if (*(seen_cmd()))
		return (ARG);
	*(seen_cmd()) = 1;
	return (CMD);
}

//Verifie les mots invalides apres le parsing et affiche une erreur
int	check_invalids(char *wrong_char)
{
	t_parsing	*tmp;

	tmp = (data())->p_start;
	while (tmp)
	{
		if (tmp->flag == INV)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			if (wrong_char[0] == '\n')
				ft_putstr_fd("newline", 2);
			else
				ft_putstr_fd(wrong_char, 2);
			ft_putstr_fd("'\n", 2);
			(data())->exit_code = 2;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

//Flag les mots de la liste chainée
int	flag_words(void)
{
	char	wrong_char[3];

	ft_memset(wrong_char, 0, sizeof(char) * 3);
	(data())->p_index = (data())->p_start;
	*(seen_cmd()) = 0;
	while ((data())->p_index)
	{
		(data())->p_index->flag = get_flag();
		(data())->p_index = (data())->p_index->next;
	}
	check_symbols(wrong_char);
	if (!check_invalids(wrong_char))
		return (0);
	return (1);
}
