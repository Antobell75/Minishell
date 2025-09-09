/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:52:47 by flren             #+#    #+#             */
/*   Updated: 2024/12/04 17:41:48 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dest[i] = src[i];
		i++ ;
	}
	while (i <= len)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	unsigned int		total;
	unsigned int		i;
	char				*dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (start > i)
	{
		dest = malloc(1);
		if (dest)
			dest[0] = '\0';
		return (dest);
	}
	total = i - start;
	if (total > len)
		total = len;
	dest = malloc(sizeof(char) * (total + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_strncpy(dest, src + start, total);
	return (dest);
}
