/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:57:04 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/20 21:03:43 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	handle_parent_process(int *input_fd, int pipe_fd[2], t_cmd *cur)
{
	ignore_signals();
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cur->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}
