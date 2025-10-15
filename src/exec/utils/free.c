/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:56:24 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 17:03:15 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_free(t_cmd *c)
{
	int	i;

	if (!c)
		return ;
	free_split(c->cmd);
	if (c->redirect)
	{
		i = 0;
		while (i < c->nb_redirect)
		{
			free(c->redirect[i].files);
			free(c->redirect[i].eof);
			i++;
		}
		free(c->redirect);
	}
	free(c->infile);
	free(c);
}

void	free_cmd_list(t_cmd *list)
{
	t_cmd	*current;
	t_cmd	*next_node;

	current = list;
	while (current)
	{
		next_node = current->next;
		cmd_free(current);
		current = next_node;
	}
}
