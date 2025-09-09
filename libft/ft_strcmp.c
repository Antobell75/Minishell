/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:52:36 by flren             #+#    #+#             */
/*   Updated: 2024/12/03 14:09:56 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1[i] == '\0' || s2[j] == '\0' )
		return (EXIT_FAILURE);
	if (s1[i] == '+')
		i++;
	if (s2[j] == '+')
		j++;
	while (s1[i] || s2[j])
	{
		if (s1[i] != s2[j])
			return (EXIT_FAILURE);
		i++;
		j++;
	}
	if (s1[i] != s2[j])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/*
int main()
{
	const char *s1 = "Hhhhhhallo";
	const char *s2 = "Hhhhhhzllo";
	size_t n = 10;

	printf("%d", ft_strncmp(s1, s2, n));
}*/
