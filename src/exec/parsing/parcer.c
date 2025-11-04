#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->nb_redirect = 0;
	new_cmd->redirect = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = -1;
	new_cmd->code = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_cmd_to_list(t_cmd **cmd, t_cmd **tmp, t_cmd *new_cmd)
{
	if (!*cmd)
		*cmd = new_cmd;
	else
		(*tmp)->next = new_cmd;
	*tmp = new_cmd;
}

int	check_redir_syntax(t_token *next)
{
	char	*error_token;

	if (!next || next->type != WORD)
	{
		if (next)
			error_token = next->value;
		else
			error_token = "newline";
		printf("bash: syntax error near unexpected token '%s'\n",
			error_token);
		return (0);
	}
	return (1);
}


static int	process_word(t_cmd *new_cmd, t_token *cur, t_var *env, int status)
{
	char	*clean_value;
	char	*expand_value;

	clean_value = remove_quotes(cur->value);
	if (!clean_value)
		return (0);
	expand_value = ft_expand(clean_value, env, status);
	free(clean_value);
	if (!expand_value)
		return (0);
	add_arg(new_cmd, expand_value);
	free(expand_value);
	return (1);
}

static int	process_redir(t_cmd *new_cmd, t_token **cur)
{
	if (!check_redir_syntax((*cur)->next))
		return (0);
	add_redirect(new_cmd, *cur);
	*cur = (*cur)->next;
	return (1);
}

static int	tokens(t_cmd *new_cmd, t_token **cur, t_var *env, int status)
{
	while (*cur && (*cur)->type != PIPE)
	{
		if ((*cur)->type == WORD)
		{
			if (!process_word(new_cmd, *cur, env, status))
				return (0);
		}
		else if ((*cur)->type == REDIR_IN || (*cur)->type == REDIR_OUT
			|| (*cur)->type == HEREDOC || (*cur)->type == REDIR_APPEND)
		{
			if (!process_redir(new_cmd, cur))
				return (0);
		}
		*cur = (*cur)->next;
	}
	return (1);
}

t_cmd	*parcing(t_token *head, t_var *env, int status)
{
	t_token	*cur;
	t_cmd	*cmd;
	t_cmd	*tail;
	t_cmd	*new_cmd;

	tail = NULL;
	cur = head;
	cmd = NULL;
	while (cur)
	{
		new_cmd = init_cmd();
		if (!new_cmd || !tokens(new_cmd, &cur, env, status))
		{
			cmd_free(new_cmd);
			return (free_cmd_list(cmd), NULL);
		}
		add_cmd_to_list(&cmd, &tail, new_cmd);
		if (cur && cur->type == PIPE)
			cur = cur->next;
	}
	return (cmd);
}

