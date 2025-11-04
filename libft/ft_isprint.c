/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:25:51 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/12 16:55:10 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*#include <stdio.h>
#include <stdlib.h>

int	main(int ac; char **av)
{
	(void)ac;
	int	a;
	a = atoi(av[1])
	printf("%d", ft_isprint(a));
	return (0);
}*/
