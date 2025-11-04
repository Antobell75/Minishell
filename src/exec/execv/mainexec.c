/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:43:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/04 23:33:28 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_cmd *cmd, t_var **env, int in_fd, int pipe_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	if (apply_redirections(cmd) != 0) // ajoute apply
		exit(1);
	if (is_builtin(cmd->cmd[0]))
		exit(exec_builtin(cmd, env, 0));
	else
		exec_external_cmd(cmd, env);
}

int	try_to_wait(int pid, int *exit_status)
{
	int	tries_count;
	int	ret;

	tries_count = 0;
	while (tries_count < 10)
	{
		ret = waitpid(pid, exit_status, 0);
		if (ret != -1)
			return (ret);
		else if (errno == EINTR)
			tries_count++;
		else
			return (-1);
	}
	return (-1);
}
static int	wait_for_children(pid_t last_pid)
{
	int	wstatus;
	int	exit_status;

	exit_status = 0;
	if (try_to_wait(last_pid, &wstatus) != -1)
	{
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			exit_status = 128 + WTERMSIG(wstatus);
			if (exit_status == 128 + SIGQUIT)
				printf("Quit(core dumped)\n");
			else if (WTERMSIG(wstatus) == SIGINT)
				printf("\n");
		}
	}
	return (exit_status);
}

static int exec_builtin_with_redir(t_cmd *cmd, t_var **env, int status)
{
	int saved_in;
	int saved_out;
	int ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) != 0)
		ret = 1;
	else
		ret = exec_builtin(cmd, env, status);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (ret);
}

static void	handle_parent_process(int *input_fd, int pipe_fd[2], t_cmd *cur)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cur->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

int	execute_pipeline(t_cmd *cmd_list, t_var **env_list, int last_status)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		input_fd;
	t_cmd	*current;

	if (!cmd_list->next && is_builtin(cmd_list->cmd[0]))
		return (exec_builtin_with_redir(cmd_list, env_list, last_status));
	input_fd = STDIN_FILENO;
	current = cmd_list;
	while (current)
	{
		if (current->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			execute_child(current, env_list, input_fd, pipe_fd);
		else if (pid > 0)
			handle_parent_process(&input_fd, pipe_fd, current);
		current = current->next;
	}
	setup_signal_handlers();
	return (wait_for_children(pid));
}
