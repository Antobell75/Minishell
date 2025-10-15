/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:33:24 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/22 01:52:37 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	count(long long n)
{
	long long	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	nb;
	long long	size;
	char		*str;

	nb = (long long)n;
	if (n < 0)
		nb = -nb;
	if (nb == 0)
		return (ft_strdup("0"));
	size = count(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (0);
	str[size--] = '\0';
	while (size >= 0)
	{
		str[size--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
