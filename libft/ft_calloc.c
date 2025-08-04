/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:39:13 by flren             #+#    #+#             */
/*   Updated: 2024/12/03 14:05:18 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*i;
	size_t				j;

	i = malloc(count * size);
	j = 0;
	if (i == 0)
		return (NULL);
	while (j < count * size)
	{
		i[j] = 0;
		j++;
	}
	return ((void *)i);
}
