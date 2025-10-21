#include "minishell.h"

static char **realloc_args(char **cmd, char *value)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		new_arr[i] = cmd[i];
		i++;
	}
	new_arr[i] = ft_strdup(value);
	if (!new_arr[i])
	{
		free(new_arr);
		return (NULL);
	}
	new_arr[i + 1] = NULL;
	return (new_arr);
}

void	add_arg(t_cmd *new_cmd, char *value)
{
	char	**new_arr;

	if (!new_cmd || !value)
		return ;
	new_arr = realloc_args(new_cmd->cmd, value);
	if (!new_arr)
		return ;
	free(new_cmd->cmd);
	new_cmd->cmd = new_arr;
}


static t_redirect	*create_redirect(t_token *cur)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = cur->type;
	redir->next = NULL;
	if (cur->next)
	{
		redir->files = ft_strdup(cur->next->value);
		if (!redir->files)
		{
			free(redir);
			return (NULL);
		}
	}
	else
		redir->files = NULL;
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

