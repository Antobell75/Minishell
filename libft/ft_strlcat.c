/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:29:46 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/20 10:11:23 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	dst_size;
	size_t	src_size;

	dst_size = ft_strlen(d);
	src_size = ft_strlen(s);
	i = 0;
	j = dst_size;
	if (size <= j || size == 0)
		return (src_size + size);
	while (s[i] && (i < size - dst_size - 1))
	{
		d[j] = s[i];
		j++;
		i++;
	}
	d[j] = '\0';
	return (src_size + dst_size);
}

/*#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	(void)ac;
	int dstsize;
	dstsize = atoi(av[3]);
	printf("%d", av[1], av[2], dstsize);
	return (0);
}*/
