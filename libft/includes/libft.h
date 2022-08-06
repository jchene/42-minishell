/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:24:01 by anguinau          #+#    #+#             */
/*   Updated: 2022/08/06 03:54:48 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char		**cp_str_tab2(char **src);
int			free_str_tab2(char **tab);
long long	ft_atoi(const char *nptr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_ischarset(char *str, char c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
int			ft_putnbr_fd(long long n, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putstrn_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
int			ft_strchr(char *str, const char *to_find);
char		*ft_strdup(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strcmp(char *str1, char *str2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(char *src, char *to_find, int n);
char		*ft_strndup(const char *s, int len, int start);
void		ft_swap(int *ptr1, int *ptr2);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			return_max(int n1, int n2);
int			return_min(int n1, int n2);
int			str_tab2_fucked_up(char	***tab, int size);

#endif