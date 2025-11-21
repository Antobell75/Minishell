/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:58:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/21 01:57:29 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_heredoc(t_redirect *redir, t_token *cur)
{
	char	*clean_n;

	redir->is_heredoc = 1;
	if (cur->next)
	{
		if (has_quotes(cur->next->value))
			redir->expand_heredoc = 0;
		else
			redir->expand_heredoc = 1;
		clean_n = remove_quotes(cur->next->value);
		if (!clean_n)
			return (0);
		redir->eof = clean_n;
		redir->files = NULL;
	}
	return (1);
}

static int	init_file_redir(t_redirect *redir, t_token *cur, t_var *env,
	int status)
{
	char	*expanded;
	char	*clean_n;

	if (cur->next)
	{
		expanded = ft_expand(cur->next->value, env, status);
		if (!expanded)
			return (0);
		if (expanded[0] == '\0' || is_ambiguous(expanded))
		{
			ft_fprintf(2, "minishell: %s: ambiguous redirect\n",
				cur->next->value);
			free(expanded);
			return (0);
		}
		clean_n = remove_quotes(expanded);
		free(expanded);
		if (!clean_n)
			return (0);
		redir->files = clean_n;
	}
	else
		redir->files = NULL;
	return (1);
}

static t_redirect	*create_redirect(t_token *cur, t_var *env, int status)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = cur->type;
	redir->next = NULL;
	redir->is_heredoc = 0;
	redir->expand_heredoc = 1;
	redir->eof = NULL;
	if (cur->type == HEREDOC)
		init_heredoc(redir, cur);
	else if (!init_file_redir(redir, cur, env, status))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	add_redirect(t_cmd *new_cmd, t_token *cur, t_var *env, int status)
{
	t_redirect	*redir;

	redir = create_redirect(cur, env, status);
	if (!redir)
		return (0);
	append_redirect(new_cmd, redir);
	new_cmd->nb_redirect++;
	return (1);
}

int	check_redir_syntax(t_token *next)
{
	char	*error_token;

	if (!next)
		error_token = "newline";
	else if (next->type != WORD)
		error_token = next->value;
	else
		return (1);
	ft_fprintf(2, " syntax error near unexpected token `%s'\n", error_token);
	return (0);
}
