/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:53:56 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/21 02:36:14 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_path_error(t_cmd *cmd, t_var **env_list)
{
	if (ft_strchr(cmd->cmd[0], '/'))
		err_msg(cmd->cmd[0], "No such file or directory", 0);
	else
		err_msg(cmd->cmd[0], "command not found", 0);
	cmd->next = NULL;
	cmd_free(cmd);
	free_env(*env_list);
	exit(127);
}

void	exec_external_cmd(t_cmd *cmd, t_var **env_list)
{
	char		*path;
	char		**envp;
	struct stat	sb;

	if (apply_redirections(cmd) != 0)
		exit(1);
	if (ft_strcmp(cmd->cmd[0], "!") == 0)
		exit(1);
	path = find_cmd_path(cmd->cmd[0], *env_list);
	if (!path)
		handle_path_error(cmd, env_list);
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", cmd->cmd[0]);
		cmd->next = NULL;
		cmd_free(cmd);
		free_env(*env_list);
		exit(126);
	}
	envp = convert_env_list(*env_list);
	execve(path, cmd->cmd, envp);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->cmd[0]);
	exit(126);
}
