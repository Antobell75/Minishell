/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:43:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 17:50:33 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_cmd *cmd, t_var **env, int in_fd, int pipe_fd[2])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (is_builtin(cmd->cmd[0]))
		exit(exec_builtin(cmd, env, 0));
	else
		exec_external_cmd(cmd, env);
}

static int	wait_for_children(pid_t last_pid)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	if (waitpid(last_pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (wait(NULL) != -1)
		;
	return (exit_status);
}

int	execute_pipeline(t_cmd *cmd_list, t_var **env_list, int last_status)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		input_fd;
	t_cmd	*current;

	if (!cmd_list->next && is_builtin(cmd_list->cmd[0]))
		return (exec_builtin(cmd_list, env_list, last_status));
	input_fd = STDIN_FILENO;
	current = cmd_list;
	while (current)
	{
		if (current->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			execute_child(current, env_list, input_fd, pipe_fd);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (current->next)
		{
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
		}
		current = current->next;
	}
	return (wait_for_children(pid));
}
