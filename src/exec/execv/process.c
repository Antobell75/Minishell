/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:53:56 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 17:55:17 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_external_cmd(t_cmd *cmd, t_var **env_list)
{
	char	*path;
	char	**envp;

	if (apply_redirections(cmd) != 0)
		exit(1);
	path = find_cmd_path(cmd->cmd[0], *env_list);
	if (!path)
	{
		err_msg(cmd->cmd[0], "command not found", 0);
		exit(127);
	}
	envp = convert_env_list(*env_list);
	execve(path, cmd->cmd, envp);
	perror("minishell");
	exit(126);
}
