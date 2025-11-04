/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:17:22 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/04 21:42:28 by anbellar         ###   ########.fr       */
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

int	ft_exit(t_cmd *cmd, t_var **env, int last_status)
{
	int fd_tty;
	
	fd_tty = open("/dev/tty", O_RDWR);
	if (fd_tty)
	{
		write(fd_tty, "exit\n", 5);
		close(fd_tty);
	}
	if (!cmd->cmd[1])
		free_exit(cmd, env, last_status);
	if (!is_numeric_str(cmd->cmd[1]))
	{
		exit_error(cmd->cmd[1], ": numeric argument required\n");
		exit(2);
	}
	if (cmd->cmd[2])
	{
		exit_error(NULL, "too many arguments\n");
		exit(1);
	}
	exit(ft_atoi(cmd->cmd[1]) % 256);
}
