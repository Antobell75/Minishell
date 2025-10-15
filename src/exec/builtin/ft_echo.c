/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:32:12 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 17:32:14 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_option(char **argv, int *start_index)
{
	int	i;
	int	j;
	int	is_option;

	is_option = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n')
		{
			j = 2;
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] == '\0')
			{
				is_option = 1;
				*start_index = i + 1;
			}
			else
				break ;
		}
		else
			break ;
		i++;
	}
	return (is_option);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->cmd[1])
	{
		if (check_n_option(cmd->cmd, &i))
			newline = 0;
		while (cmd->cmd[i])
		{
			printf("%s", cmd->cmd[i]);
			if (cmd->cmd[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline)
		printf("\n");
	return (0);
}
