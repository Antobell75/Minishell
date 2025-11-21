/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:58:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/20 21:40:48 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_heredoc(void)
{
	char	*line;

	g_sig = 0;
	line = readline("> ");
	return (line);
}

static int	err_msg_heredoc(void)
{
	if (g_sig == SIGINT)
		return (-1);
	ft_fprintf(2, "minishell: warning: here-document delimited");
	return (err_msg("minishell", " by end-of-file (wanted `%s')\n", 0));
}

int	read_heredoc_lines(int pipefd[2], t_redirect *redir, t_var *env)
{
	char	*line;

	if (!redir || !redir->eof)
		return (-1);
	while (1)
	{
		if (g_sig)
			return (-1);
		line = readline_heredoc();
		if (!line)
			return (err_msg_heredoc());
		if (ft_strcmp(line, redir->eof) == 0)
			return (free(line), 0);
		if (process_heredoc_line(pipefd[1], redir, line, env) == -1)
			return (-1);
	}
	return (0);
}
