/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:28:22 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/15 03:39:56 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_w(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s && *s != c)
			++count;
		while (*s && *s != c)
			++s;
	}
	return (count);
}

int	malloc_str(char **str, int size)
{
	*str = malloc(sizeof(char) * size + 1);
	if (!*str)
		return (0);
	(*str)[size] = '\0';
	return (1);
}

int	malloc_str_tab(char ***str, int size)
{
	*str = (char **)malloc(sizeof(char *) * (size + 1));
	if (!*str)
		return (0);
	(*str)[size] = NULL;
	return (1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*send;

	i = 0;
	while (s && s[i])
		i++;
	if (i < start)
	{
		if (!s || !malloc_str(&str, 0))
			return (NULL);
		return (str);
	}
	i = 0;
	while (s && s[start++] && len--)
		i++;
	if (!s || !malloc_str(&str, i))
		return (NULL);
	send = str;
	start -= i + 1;
	while (s[start] && i--)
		*str++ = s[start++];
	return (send);
}

// Malloc & return un char** qui contient S séparée de C
char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		start;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	count = count_w(s, c);
	if (!malloc_str_tab(&str, count))
		return (NULL);
	j = 0;
	while (i < count)
	{
		while (s[j] && s[j] == c)
			++j;
		start = j;
		while (s[j] && s[j] != c)
			++j;
		str[i++] = ft_substr(s, start, j - start);
		if (!(str[i - 1]))
			return (NULL);
	}
	return (str);
}
