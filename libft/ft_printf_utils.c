/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:13:37 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/13 21:55:40 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_p(void *ptr, int count, int check, int fd)
{
	uintptr_t	u;

	u = (uintptr_t)ptr;
	if (u == 0)
	{
		count = ft_putstr("(nil)", count, fd);
		return (count);
	}
	else if (check == 0)
	{
		count = ft_putstr("0x", count, fd);
		check++;
	}
	if (u >= 16)
		count = ft_printf_p((void *)(uintptr_t)(u / 16), count, check, fd);
	count += ft_putchar("0123456789abcdef"[u % 16], fd);
	return (count);
}

int	ft_printf_di(int n, int count, int fd)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		count += 11;
	}
	else if (n < 0)
	{
		count += ft_putchar('-', fd);
		n *= -1;
	}
	if (n >= 10)
		count = ft_printf_di(n / 10, count, fd);
	if (n != -2147483648)
		count += ft_putchar(n % 10 + '0', fd);
	return (count);
}

int	ft_printf_lowerx(unsigned int n, int count, int fd)
{
	if (n == 0)
		count += ft_putchar('0', fd);
	else if (n >= 16)
	{
		count = ft_printf_lowerx(n / 16, count, fd);
		count = ft_printf_lowerx(n % 16, count, fd);
	}
	else
	{
		if (n <= 9)
			count += ft_putchar(n + '0', fd);
		else
			count += ft_putchar(n + 'a' - 10, fd);
	}
	return (count);
}

int	ft_printf_upperx(unsigned int n, int count, int fd)
{
	if (n == 0)
		count += ft_putchar('0', fd);
	else if (n >= 16)
	{
		count = ft_printf_upperx(n / 16, count, fd);
		count = ft_printf_upperx(n % 16, count, fd);
	}
	else
	{
		if (n <= 9)
			count += ft_putchar(n + '0', fd);
		else
			count += ft_putchar(n + 'A' - 10, fd);
	}
	return (count);
}

int	ft_printf_u(unsigned int n, int count, int fd)
{
	if (n < 10)
		count += ft_putchar(n + '0', fd);
	else
	{
		count = ft_printf_u(n / 10, count, fd);
		count += ft_putchar(n % 10 + '0', fd);
	}
	return (count);
}
