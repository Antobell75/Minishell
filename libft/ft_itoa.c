/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flren <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:22:18 by flren             #+#    #+#             */
/*   Updated: 2024/12/04 20:34:18 by flren            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_check(void)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	if (dest == NULL)
		return (NULL);
	dest[0] = '0';
	dest[1] = '\0';
	return (dest);
}

int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_print(long n, int len, char *str)
{
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	long	num;

	num = (long)n;
	sign = 0;
	int (len) = ft_len(num);
	if (num == 0)
		return (ft_check());
	if (num < 0)
	{
		sign = 1;
		num = -num;
		len++;
	}
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	ft_print(num, len, str);
	if (sign)
		str[0] = '-';
	return (str);
}

/*int main()
{
	int	src = -9;
	char	*dest;
	
	dest = ft_itoa(src);
	printf("%s", dest);
	free(dest);
}*/
