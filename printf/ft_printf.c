/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:24:27 by anbellar          #+#    #+#             */
/*   Updated: 2025/02/11 18:04:23 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str, int count)
{
	int	i;

	i = 0;
	if (!str)
		count = ft_putstr("(null)", count);
	else
	{
		while (str[i])
		{
			count += ft_putchar(str[i]);
			i++;
		}
	}
	return (count);
}

int	ft_pourcent(const char *str, va_list args, int i, int count)
{
	int	check;

	check = 0;
	if (str[i] == 'c')
		count += ft_putchar((char)va_arg(args, int));
	else if (str[i] == 's')
		count = ft_putstr(va_arg(args, char *), count);
	else if (str[i] == 'd' || str[i] == 'i')
		count = ft_printf_di(va_arg(args, int), count);
	else if (str[i] == 'x')
		count = ft_printf_lowerx(va_arg(args, unsigned int), count);
	else if (str[i] == 'X')
		count = ft_printf_upperx(va_arg(args, unsigned int), count);
	else if (str[i] == 'u')
		count = ft_printf_u(va_arg(args, unsigned int), count);
	else if (str[i] == 'p')
		count = ft_printf_p(va_arg(args, void *), count, check);
	else if (str[i] == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			count = ft_pourcent(format, args, ++i, count);
		else
		{
			count++;
			write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (count);
}
