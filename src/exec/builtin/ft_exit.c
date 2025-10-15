/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:17:22 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 17:27:38 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
}

int	ft_exit(t_cmd *cmd, int last_status)
{
	printf("exit\n");
	if (!cmd->cmd[1])
		exit(last_status);
	if (!is_numeric_str(cmd->cmd[1]))
	{
		exit_error(cmd->cmd[1], ": numeric argument required\n");
		exit(255);
	}
	if (cmd->cmd[2])
	{
		exit_error(NULL, "too many arguments\n");
		exit(1);
	}
	exit(ft_atoi(cmd->cmd[1]) % 256);
}
