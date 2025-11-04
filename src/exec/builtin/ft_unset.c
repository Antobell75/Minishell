/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:18:21 by dwsasd            #+#    #+#             */
/*   Updated: 2025/11/04 21:45:37 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_var_node(t_var *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

static void	find_and_remove_var(char *name, t_var **env_list)
{
	t_var	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->prev == NULL)
				*env_list = current->next;
			else
				current->prev->next = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free_var_node(current);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(t_cmd *cmd, t_var **env_list)
{
	int	i;

	if (!cmd->cmd[1])
		return (0);
	i = 1;
	while (cmd->cmd[i])
	{
		find_and_remove_var(cmd->cmd[i], env_list);
		i++;
	}
	return (0);
}
