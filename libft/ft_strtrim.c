/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:18:45 by flren             #+#    #+#             */
/*   Updated: 2024/12/03 16:11:47 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_l(const char *s1, const char *set)
{
	size_t	i;
	size_t	start;
	size_t	fin;
	size_t	len;

	i = 0;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (s1[start] == '\0')
		return (0);
	while (s1[i])
		i++;
	fin = i - 1;
	while (fin > start && ft_strchr(set, s1[fin]))
		fin--;
	len = fin - start + 1;
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*dest;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_l(s1, set);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[start]))
		start++;
	while (i < len)
	{
		dest[i] = s1[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main()
{
	char *str = "   H >>>>>e >>>l l o     ";
	char *set = " >";
	char *dest;

	dest = ft_strtrim(str, set);
	printf("%s", dest);
}*/
