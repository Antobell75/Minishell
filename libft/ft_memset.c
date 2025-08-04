/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:57:28 by flren             #+#    #+#             */
/*   Updated: 2024/11/23 13:29:03 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (p);
}
