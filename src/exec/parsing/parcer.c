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
	{
		*cmd = new_cmd;
		*tmp = new_cmd;
	}
	else
	{
		(*tmp)->next = new_cmd;
		*tmp = new_cmd;
	}
}

static int	is_redirect(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == REDIR_APPEND);
}

static t_token	*process_tokens(t_cmd *new_cmd, t_token *cur)
{
	while (cur && cur->type != PIPE)
	{
		if (cur->type == WORD)
			add_arg(new_cmd, cur->value);
		else if (is_redirect(cur->type))
		{
			add_redirect(new_cmd, cur);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (cur);
}

t_cmd	*parcing(t_token *head)
{
	t_token	*cur;
	t_cmd	*cmd;
	t_cmd	*tmp;
	t_cmd	*new_cmd;

	tmp = NULL;
	cur = head;
	cmd = NULL;
	while (cur)
	{
		new_cmd = init_cmd();
		cur = process_tokens(new_cmd, cur);
		add_cmd_to_list(&cmd, &tmp, new_cmd);
		if (cur && cur->type == PIPE)
			cur = cur->next;
	}
	return (cmd);
}

