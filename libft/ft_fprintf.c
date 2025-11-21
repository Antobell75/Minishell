/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:24:27 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/20 18:57:21 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr(char *str, int count, int fd)
{
	int	i;

	i = 0;
	if (!str)
		count = ft_putstr("(null)", count, fd);
	else
	{
		while (str[i])
		{
			count += ft_putchar(str[i], fd);
			i++;
		}
	}
	return (count);
}

int	ft_pourcent(const char *str, va_list args, t_print *fptf)
{
	if (str[fptf->i] == 'c')
		fptf->count += ft_putchar((char)va_arg(args, int), fptf->fd);
	else if (str[fptf->i] == 's')
		fptf->count = ft_putstr(va_arg(args, char *), fptf->count, fptf->fd);
	else if (str[fptf->i] == 'd' || str[fptf->i] == 'i')
			fptf->count = ft_printf_di(va_arg(args, int),
				fptf->count, fptf->fd);
	else if (str[fptf->i] == 'x')
		fptf->count = ft_printf_lowerx(va_arg(args, unsigned int),
				fptf->count, fptf->fd);
	else if (str[fptf->i] == 'X')
		fptf->count = ft_printf_upperx(va_arg(args, unsigned int),
				fptf->count, fptf->fd);
	else if (str[fptf->i] == 'u')
		fptf->count = ft_printf_u(va_arg(args, unsigned int),
				fptf->count, fptf->fd);
	else if (str[fptf->i] == 'p')
		fptf->count = ft_printf_p(va_arg(args, void *), fptf->count,
				fptf->check, fptf->fd);
	else if (str[fptf->i] == '%')
		fptf->count += ft_putchar('%', fptf->fd);
	return (fptf->count);
}

void	init_print(t_print *fptf, int fd)
{
	fptf->i = 0;
	fptf->count = 0;
	fptf->check = 0;
	fptf->di = 0;
	fptf->fd = fd;
	fptf->lowerx = 0;
	fptf->upperx = 0;
	fptf->ptr = 0;
	fptf->u = 0;
}

int	ft_fprintf(int fd, const char *format, ...)
{
	t_print	fptf;

	if (!format || fd < 0)
		return (-1);
	init_print(&fptf, fd);
	va_start(fptf.args, format);
	fptf.format = format;
	while (fptf.format[fptf.i])
	{
		if (fptf.format[fptf.i] == '%')
		{
			fptf.i++;
			fptf.count = ft_pourcent(fptf.format, fptf.args, &fptf);
		}
		else
		{
			fptf.count++;
			write(fptf.fd, &fptf.format[fptf.i], 1);
		}
		fptf.i++;
	}
	va_end(fptf.args);
	return (fptf.count);
}
