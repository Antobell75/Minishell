/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:56:24 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/16 16:12:09 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cmd_free(t_cmd *c)
{
	t_redirect	*redir;
	t_redirect	*next_redir;

	if (!c)
		return ;
	if (c->cmd)
		free_split(c->cmd);

	redir = c->redirect;
	while (redir)
	{
		next_redir = redir->next;
		if (redir->files)
			free(redir->files);
		if (redir->eof)
			free(redir->eof);
		free(redir);
		redir = next_redir;
	}

	if (c->infile)
		free(c->infile);
	free(c);
}


void	free_cmd_list(t_cmd *list)
{
	t_cmd	*current;
	t_cmd	*next_node;

	current = list;
	while (current)
	{
		next_node = current->next;
		cmd_free(current);
		current = next_node;
	}
}

void	free_env(t_var *env)
{
	t_var	*current;
	t_var	*next_node;

	current = env;
	while (current)
	{
		next_node = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next_node;
	}
}

void	free_exit(t_cmd *cmd, t_var **env, int last_status)
{
	if (env)
		free_env(*env);
	if (cmd)
		free_cmd_list(cmd);
	exit(last_status);
}
