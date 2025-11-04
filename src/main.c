/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:00:51 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/04 23:34:51 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_line(char *line, t_var *env, int status)
{
	t_token	*tokens;
	t_cmd	*commands;

	(void)env;
	if (!line || line[0] == '\0')
		return (NULL);

	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	commands = parcing(tokens, env, status);
	free_token_list(tokens);
	if (!commands)
		return (NULL);

	return (commands);
}


static int	process_line(char *line, t_var **env, int status)
{
	t_cmd	*cmd_list;

	if (line[0] == '\0')
		return (status);
	cmd_list = parse_line(line, *env, status);
	if (cmd_list && g_sig == 0)
		add_history(line);
	if (cmd_list)
	{
		if (process_heredocs(cmd_list) == -1)
		{
			status = 130;
			g_sig = 0;
		}
		else
			status = execute_pipeline(cmd_list, env, status);
		free_cmd_list(cmd_list);
	}
	return (status);
}


static int	shell_loop_iteration(t_var **env, int status)
{
	char	*line;

	g_sig = 0;
	line = readline("minishell$ ");
	if (g_sig == SIGINT)
		status = 130;
	if (!line) // detection de crl + D
	{
		printf("exit\n"); // ecrire sur la sortie /dev/tty
		return (-1); // atttention l'exit code de sortie pour ctr + D est pas bon il faut le dernier exit code 
	}
	if (line[0] != '\0' && g_sig == 0)
	{
		add_history(line);
		status = process_line(line, env, status);
	}
	free(line);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	t_var	*env;
	int		status;

	(void)ac;
	(void)av;
	env = create_env(envp);
	if (!env)
		return (0);
	setup_signal_handlers();//
	status = 0;
	while (status != -1)
		status = shell_loop_iteration(&env, status);
	rl_clear_history();
	free_env(env);
	if (status == -1)
		return (0);
	else
		return (status);
}

