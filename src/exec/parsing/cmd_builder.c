/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:58:31 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 16:58:32 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Alloue et initialise une nouvelle structure t_cmd.
t_cmd	*cmd_new(char **argv, int *infile_fd, int outfile_fd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = argv;
	new_cmd->nb_redirect = 0;
	new_cmd->redirect = NULL;
	new_cmd->infile = infile_fd;
	new_cmd->outfile = outfile_fd;
	new_cmd->code = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}
