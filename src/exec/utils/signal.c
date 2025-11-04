/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:16:01 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/04 22:52:53 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sig = 0; // je sais pas si ce seule variable glob

static void	on_signal(int signo)
{
	g_sig = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	heredoc_signal(int signo)
{
	int	fd;

	g_sig = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		fd = open("/dev/tty", O_RDONLY);
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			if (fd > 2)
				close(fd);
		}
	}
}

void	sigchld_handler(int signo)
{
	int	status;

	(void)signo;
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_chld;

	sa_int.sa_handler = on_signal;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_int, NULL);
	sa_chld.sa_handler = sigchld_handler;
	sigemptyset(&sa_chld.sa_mask);
	sa_chld.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	sigaction(SIGCHLD, &sa_chld, NULL);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = heredoc_signal;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
