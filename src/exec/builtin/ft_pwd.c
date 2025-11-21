/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:22:50 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/21 02:39:46 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (cmd->cmd[1])
	{
		if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1])
		{
			ft_fprintf(2,
				"minishell: pwd: -%c: invalid option\n", cmd->cmd[1][1]);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
