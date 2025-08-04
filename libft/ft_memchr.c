/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:04:47 by flren             #+#    #+#             */
/*   Updated: 2025/07/28 15:09:44 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*s;
	size_t		i;

	s = (const char *) str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (char) c)
			return ((void *) &s[i]);
		i++;
	}
	return (NULL);
}
