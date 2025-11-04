#include "minishell.h"

char	*readline_heredoc(void)
{
	char	*line;

	g_sig = 0;
	line = readline("> ");
	return (line);
}

static int	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

static int	read_heredoc_lines(int pipefd[2], t_redirect *redir)
{
	char	*line;

	while (1)
	{
		if (g_sig)
			return (-1);
		line = readline_heredoc();
		if (!line)
		{
			if (g_sig == SIGINT)
				return (-1);
			printf("minishell: warning: here-document delimited");
			printf(" by end-of-file (wanted `%s')\n", redir->eof);
			break ;
		}
		if (ft_strcmp(line, redir->eof) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipefd[1], line);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_redirect *redir, t_cmd *cmd)
{
	int		pipefd[2];
	int		ret;

	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals();
	ret = read_heredoc_lines(pipefd, redir);
	setup_signal_handlers();
	if (ret == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	if (cmd->infile && *cmd->infile != -1)
		close(*cmd->infile);
	if (!cmd->infile)
		cmd->infile = malloc(sizeof(int));
	*cmd->infile = pipefd[0];
	return (0);
}

int	process_heredocs(t_cmd *cmd_list)
{
	t_cmd		*current;
	t_redirect	*redir;

	current = cmd_list;
	while (current)
	{
		redir = current->redirect;
		while (redir)
		{
			if (redir->is_heredoc)
			{
				if (handle_heredoc(redir, current) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}
