#include "minishell.h"

static int	init_heredoc(t_redirect *redir, t_token *cur)
{
	redir->is_heredoc = 1;
	if (cur->next)
		redir->eof = ft_strdup(cur->next->value);
	redir->files = NULL;
	return (1);
}

static int	init_file_redir(t_redirect *redir, t_token *cur)
{
	if (cur->next)
	{
		redir->files = ft_strdup(cur->next->value);
		if (!redir->files)
			return (0);
	}
	else
		redir->files = NULL;
	return (1);
}

static t_redirect	*create_redirect(t_token *cur)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = cur->type;
	redir->next = NULL;
	redir->is_heredoc = 0;
	redir->eof = NULL;
	if (cur->type == HEREDOC)
		init_heredoc(redir, cur);
	else if (!init_file_redir(redir, cur))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

static void	append_redirect(t_cmd *cmd, t_redirect *redir)
{
	t_redirect	*tmp;

	if (!cmd->redirect)
		cmd->redirect = redir;
	else
	{
		tmp = cmd->redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

void	add_redirect(t_cmd *new_cmd, t_token *cur)
{
	t_redirect	*redir;

	redir = create_redirect(cur);
	if (!redir)
		return ;
	append_redirect(new_cmd, redir);
	new_cmd->nb_redirect++;
}