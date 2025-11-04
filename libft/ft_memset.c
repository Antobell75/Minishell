/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:26:39 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/19 14:53:09 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

/*#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	(void)ac;
	int c;
	int	len;
	char b = av[1]
	c = atoi(av[2]);
	len = atoi(av[3]);
	ft_memset(b, c, len);
	printf("%s", b);
	return (0);
}*/
