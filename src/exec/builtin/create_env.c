/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:33:13 by anbellar          #+#    #+#             */
/*   Updated: 2025/10/15 16:35:22 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*new_var(char *envp_line)
{
	t_var	*new;
	char	*equal_pos;

	equal_pos = ft_strchr(envp_line, '=');
	if (!equal_pos)
		return (NULL);
	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = ft_strndup(envp_line, equal_pos - envp_line);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(equal_pos + 1);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_var	*create_env(char **envp)
{
	t_var	*head;
	t_var	*current;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	head = new_var(envp[0]);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (envp[i])
	{
		current->next = new_var(envp[i]);
		if (!current->next)
		{
			free_env(head);
			return (NULL);
		}
		current->next->prev = current;
		current = current->next;
		i++;
	}
	return (head);
}
