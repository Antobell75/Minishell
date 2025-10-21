/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:00:51 by sle-bail          #+#    #+#             */
/*   Updated: 2025/10/16 16:16:58 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_line(char *line, t_var *env)
{
	t_token	*tokens;
	t_cmd	*commands;

	(void)env;
	if (!line || line[0] == '\0')
		return (NULL);

	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);

	commands = parcing(tokens);
	free_token_list(tokens);

	return (commands);
}


void	free_commands(t_cmd *commands)
{
	t_cmd	*current_node;
	t_cmd	*next_node;

	current_node = commands;
	while (current_node)
	{
		next_node = current_node->next;
		free_string_array(current_node->cmd);
		free(current_node);
		current_node = next_node;
	}
}

// main
static int	process_line(char *line, t_var **env, int status)
{
	t_cmd	*cmd_list;

	if (line[0] == '\0')
		return (status);
	cmd_list = parse_line(line, *env);
	add_history(line);
	if (cmd_list)
	{
		status = execute_pipeline(cmd_list, env, status);
		free_cmd_list(cmd_list);
	}
	return (status);
}

static int	shell_loop_iteration(t_var **env, int status)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (-1);
	status = process_line(line, env, status);
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

