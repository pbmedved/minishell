/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:37:19 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/21 14:58:39 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_mass_memdel(char **s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		free(s[i]);
		s[i] = (void*)0;
		i++;
	}
}

static size_t	ft_strlen_chr(char *str, char c, size_t i)
{
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_split_words_count(const char *s, char c)
{
	size_t		words_count;
	size_t		i;

	if (!s)
		return (-2);
	i = 0;
	words_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words_count++;
		i++;
	}
	return (words_count);
}

char			**ft_split(char const *s, char c)
{
	char		**splited;
	size_t		i;
	size_t		ic;

	if (!(splited = (char**)malloc \
((ft_split_words_count(s, c) + 1) * sizeof(char*))))
		return ((void*)0);
	ic = 0;
	i = 0;
	while (ic < ft_split_words_count(s, c))
	{
		while (s[i] == c)
			i++;
		if (!(splited[ic++] = ft_substr \
((char*)s, i, ft_strlen_chr((char*)s, c, i) - i)))
		{
			ft_mass_memdel(splited, ic);
			free(splited);
			return ((void*)0);
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	splited[ic] = ((void*)0);
	return (splited);
}
