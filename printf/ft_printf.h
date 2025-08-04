/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:36:21 by anbellar          #+#    #+#             */
/*   Updated: 2025/01/14 19:17:51 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <string.h>

int		ft_pourcent(const char *str, va_list args, int i, int count);
int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str, int count);
int		ft_printf_di(int n, int count);
int		ft_printf_lowerx(unsigned int n, int count);
int		ft_printf_upperx(unsigned int n, int count);
int		ft_printf_u(unsigned int n, int count);
int		ft_printf_p(void *ptr, int count, int check);

#endif
