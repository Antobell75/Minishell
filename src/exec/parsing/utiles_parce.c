/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_parce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:58:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/21 01:13:45 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_skip(char *src, int *i, char *quote)
{
	if (src[*i] == '$' && !*quote && src[*i + 1] == '\'')
	{
		*quote = '\'';
		(*i)++;
		return (1);
	}
	if ((src[*i] == '\'' || src[*i] == '"') && !*quote)
	{
		*quote = src[*i];
		return (1);
	}
	if (src[*i] == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	remove_quotes_process(char *src, char *dst)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (!should_skip(src, &i, &quote))
		{
			if (dst)
				dst[j++] = src[i];
			else
				j++;
		}
		i++;
	}
	if (dst)
		dst[j] = '\0';
	return (j);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*res;

	if (!str)
		return (NULL);
	len = remove_quotes_process(str, NULL);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	remove_quotes_process(str, res);
	return (res);
}

int	get_token_len(char *s)
{
	int		i;
	int		qlen;

	i = 0;
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
	{
		if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>')
			|| (s[0] == '<' && s[1] == '>'))
			return (2);
		return (1);
	}
	while (s[i] && !is_whitespace(s[i]) && !is_special(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qlen = check_quote(&s[i]);
			if (qlen < 0)
				return (-1);
			i += qlen;
		}
		else
			i++;
	}
	return (i);
}

char	*ft_chrdup(char c)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (NULL);
	s[0] = c;
	s[1] = 0;
	return (s);
}
