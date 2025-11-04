/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:34:33 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/20 11:30:24 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	i;
	size_t	j;

	n = ft_strlen(needle);
	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (j == n)
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
#include <stdlib.H>

int	main(int ac, char **av)
{
	(void)ac;
	int len;
	len = atoi(av[3]);
	printf("%s", av[1], av[2], len);
	return (0);
}*/
