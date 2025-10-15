/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:17:04 by anbellar          #+#    #+#             */
/*   Updated: 2025/10/15 16:09:16 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*find_var(t_var *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	add_var_to_env(t_var **env_list, char *name, char *value)
{
	t_var	*new_var;
	t_var	*current;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
	{
		free(name);
		free(value);
		return ;
	}
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
	if (!*env_list)
	{
		*env_list = new_var;
		new_var->prev = NULL;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_var;
	new_var->prev = current;
}

static void	handle_export_arg(char *arg, t_var **env_list)
{
	char	*name;
	char	*value;
	char	*equal_pos;
	t_var	*existing_var;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		name = ft_strdup(arg);
	else
		name = ft_strndup(arg, equal_pos - arg);
	value = NULL;
	if (equal_pos)
		value = ft_strdup(equal_pos + 1);
	existing_var = find_var(*env_list, name);
	if (existing_var)
	{
		free(name);
		if (value)
		{
			free(existing_var->value);
			existing_var->value = value;
		}
	}
	else
		add_var_to_env(env_list, name, value);
}

static int	print_export(t_var *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_var **env_list)
{
	int	i;

	if (!cmd->cmd[1])
		return (print_export(*env_list));
	i = 1;
	while (cmd->cmd[i])
	{
		handle_export_arg(cmd->cmd[i], env_list);
		i++;
	}
	return (0);
}
