/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:27:28 by flren             #+#    #+#             */
/*   Updated: 2024/12/05 17:26:00 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (dest);
	s = (const char *)src;
	d = (char *)dest;
	while (n--)
	{
		*d++ = *s++;
	}
	return ((void *)dest);
}
/*int main()
{
	char *dest;
	const char *src = "Hallo";
	size_t n = 1;

	dest = (char *)malloc(n);
	if (dest == NULL)
	{
		printf("%s", "fail malloc");
		return (1);
	}
	char *r = ft_memcpy(dest, src, n);
	if (r != NULL)
		printf("%s", "Trouver");
	else
		printf("%s", "Non Trouver");
}*/
