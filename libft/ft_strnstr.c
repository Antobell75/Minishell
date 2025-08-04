/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:14:42 by flren             #+#    #+#             */
/*   Updated: 2024/12/05 18:13:48 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = 0;
	if (!*little || big == little)
		return ((char *) big);
	if (big == NULL && len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		l = 0;
		while (little[l] && i + l < len && big[i + l] == little[l])
		{
			l++;
		}
		if (little[l] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
