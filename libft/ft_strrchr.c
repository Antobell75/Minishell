/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:31:32 by flren             #+#    #+#             */
/*   Updated: 2024/12/05 18:13:14 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char) c)
			return ((char *)&str[i]);
		i--;
	}
	if (c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}

/*int main()
{
	const char *str = "Hello, World !";
	char c = 'a';

	printf("%s", ft_strrchr(str, c));
}*/
