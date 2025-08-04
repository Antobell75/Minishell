/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:30 by flren             #+#    #+#             */
/*   Updated: 2024/11/25 14:18:54 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_move(unsigned char *dest, const unsigned char *src, size_t len)
{
	size_t	i;

	if (dest < src)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			dest[i] = src[i];
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (0);
	if (dest == src || len == 0)
		return (dest);
	return (ft_move(d, s, len));
}
