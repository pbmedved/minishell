/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:45:26 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/22 00:25:02 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_reallocpy(char *old, char c)
{
	size_t 		cur_size;
	char		*young;

	if (!old)
		cur_size = 0;
	else
		cur_size = ft_strlen(old);
	if (!(young = calloc(cur_size+2, 1)))
		exit_error("Malloc error", 1);
	ft_strlcpy(young, old, cur_size+1);
	young[cur_size] = c;
	free(old);
	return (young);
}
char	*str_reallocpy_str(char *old, char *new)
{
	size_t 		cur_size;
	char		*young;

	if (!new)
		return (old);
	if (!old)
		cur_size = 0;
	else
		cur_size = ft_strlen(old);
	if (!(young = ft_calloc(cur_size + ft_strlen(new) + 1, 1)))
		exit_error("Malloc error", errno);
	ft_strlcpy (young, old, cur_size + 1);
	ft_strlcat (young, new, ft_strlen(new)+cur_size + 1);
	free(old);
	return (young);
}
//echo "$USER $PATH $PWD"
int			ft_strncmp_revers(char *in, char *this, size_t n)
{
	size_t in_len;
	size_t this_len;

	in_len = ft_strlen(in) - 1;
	this_len = ft_strlen(this) - 1;
	while (n-- > 0)
	{
		if ((unsigned char)in[in_len] == '\0' || (unsigned char)this[this_len] == '\0' \
		|| ((unsigned char)in[in_len] != (unsigned char)this[this_len]))
		{
			if ((unsigned char)in[in_len] == (unsigned char)this[this_len])
				return (0);
			return ((unsigned char)in[in_len] - (unsigned char)this[this_len] > 0 ? 1 : -1);
		}
		in_len--;
		this_len--;
	}
	return (0);
}

int 		whitespace_remove(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}