/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_lexpars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:13:56 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/21 01:57:27 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	handle_backslash(char *res, int *i, char *str, int *j)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		res[(*j)++] = str[*i];
		(*i)++;
		return (1);
	}
	return (0);
}*/

int	pipe_error(t_cmd *cmd)
{
	ft_fprintf(2, " syntax error near unexpected token `|'\n");
	return (free_cmd_list(cmd), 2);
}

int	process_redir(t_cmd *new_cmd, t_token **cur, t_parse_info *info)
{
	if (!check_redir_syntax((*cur)->next))
	{
		if (info->error_code)
			*info->error_code = 2;
		return (0);
	}
	if (!add_redirect(new_cmd, *cur, info->env, info->status))
	{
		if (info->error_code)
			*info->error_code = 1;
		return (0);
	}
	*cur = (*cur)->next;
	return (1);
}

void	append_redirect(t_cmd *cmd, t_redirect *redir)
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

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	is_ambiguous(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (!quote && is_whitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}
