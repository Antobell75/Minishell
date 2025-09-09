/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:37:40 by flren             #+#    #+#             */
/*   Updated: 2024/12/09 16:28:23 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	in;

	i = 0;
	count = 0;
	in = 0;
	while (s[i])
	{
		if (s[i] != c && in == 0)
		{
			in = 1;
			count++;
		}
		else if (s[i] == c)
			in = 0;
		i++;
	}
	return (count);
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_free(char **dest, size_t i)
{
	while (i > 0)
	{
		free (dest[i - 1]);
		i--;
	}
	free (dest);
}

char	**ft_cpy(char **dest, const char *s, char c, size_t i)
{
	size_t	word_len;

	while (*s)
	{
		if (*s != c)
		{
			word_len = 0;
			while (s[word_len] && s[word_len] != c)
				word_len++;
			dest[i] = ft_strndup(s, word_len);
			if (dest[i] == NULL)
			{
				ft_free(dest, i);
				return (NULL);
			}
			i++;
			s = s + word_len;
		}
		else
			s++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	word_count;
	char	**dest;

	i = 0;
	if (s == NULL)
		return (NULL);
	word_count = ft_count_word(s, c);
	dest = malloc(sizeof(char *) * (word_count + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_cpy(dest, s, c, i);
	if (dest == NULL)
		return (NULL);
	return (dest);
}

/*int main() 
{
	char **result = ft_split("Hello moi, c'est du C!", ' ');

	int i = 0;
	while (result[i] != NULL) 
	{
		printf("%s\n", result[i]);
        	i++;
    	}
	free (result);
}*/
