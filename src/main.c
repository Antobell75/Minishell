/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:00:51 by sle-bail          #+#    #+#             */
/*   Updated: 2025/10/15 21:46:43 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fake parsing
char **duplicate_argv(const char **argv)
{
	int i = 0;
	while (argv[i])
		i++;
	char **new_argv = malloc(sizeof(char *) * (i + 1));
	if (!new_argv)
		return (NULL);
	for (int j = 0; j < i; j++)
		new_argv[j] = ft_strdup(argv[j]);
	new_argv[i] = NULL;
	return (new_argv);
}

t_cmd *create_test_cmd(const char **argv, int nb_redirects)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	
	cmd->cmd = duplicate_argv(argv);
	cmd->nb_redirect = nb_redirects;
	if (nb_redirects > 0)
		cmd->redirect = malloc(sizeof(t_redirect) * nb_redirects);
	else
		cmd->redirect = NULL;
	cmd->infile = NULL;
	cmd->outfile = -1;
	cmd->code = 0;
	cmd->next = NULL;
	return (cmd);
}

void add_test_redirect(t_cmd *cmd, int index, int type, const char *file, int is_heredoc)
{
	if (!cmd || index >= cmd->nb_redirect)
		return;
	cmd->redirect[index].type = type;
	cmd->redirect[index].files = ft_strdup(file);
	cmd->redirect[index].eof = NULL;
	cmd->redirect[index].is_heredoc = is_heredoc;
}

static t_cmd	*parse_line(char *line, t_var *env)
{
	char	**pipe_segments;
	t_cmd	*head;
	t_cmd	*current;
	int		i;

	(void)env;
	head = NULL;
	current = NULL;
	pipe_segments = ft_split(line, '|');
	if (!pipe_segments)
		return (NULL);
	i = 0;
	while (pipe_segments[i])
	{
		t_cmd *new_cmd = cmd_new(ft_split(pipe_segments[i], ' '), NULL, -1);
		if (!head)
		{
			head = new_cmd;
			current = head;
		}
		else
		{
			current->next = new_cmd;
			current = current->next;
		}
		i++;
	}
	free_split(pipe_segments);
	return (head);
}
// fin du fake parsing


// main
int	main(int ac, char **av, char **envp)
{
	t_var	*env;
	t_cmd	*cmd_list;
	char	*line;
	int		last_status;

	(void)ac;
	(void)av;
	env = create_env(envp);
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (line[0] != '\0')
		{
			cmd_list = parse_line(line, env);
			add_history(line);
			if (cmd_list)
			{
				last_status = execute_pipeline(cmd_list, &env, last_status);
				free_cmd_list(cmd_list);
			}
		}
		free(line);
	}
	free_env(env);
	return (last_status);
}
