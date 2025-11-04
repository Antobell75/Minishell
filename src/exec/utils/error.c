/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:58:04 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 16:58:09 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(const char *pfx, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (pfx)
	{
		ft_putstr_fd(pfx, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}
