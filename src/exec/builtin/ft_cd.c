/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:16:02 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 16:16:35 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_var **env_list, char *name, char *value)
{
	t_var	*var;

	var = *env_list;
	while (var)
	{
		if (ft_strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = value;
			return ;
		}
		var = var->next;
	}
	// Si la variable n'a pas été trouvée, on la crée (comme export).
	// Tu devrais avoir une fonction pour ça dans ton ft_export.
	// add_var_to_env(env_list, ft_strdup(name), value);
	(void)value; // Pour le moment, on ne gère que la mise à jour.
}

static char	*get_target_path(t_cmd *cmd, t_var *env)
{
	char	*path;

	if (!cmd->cmd[1]) // 'cd' seul
	{
		path = get_env_value("HOME", env);
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (path);
	}
	if (ft_strcmp(cmd->cmd[1], "-") == 0) // 'cd -'
	{
		path = get_env_value("OLDPWD", env);
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			printf("%s\n", path);
		return (path);
	}
	return (cmd->cmd[1]);
}

int	ft_cd(t_cmd *cmd, t_var **env_list)
{
	char	*target_path;
	char	*old_pwd;
	char	*current_pwd;

	target_path = get_target_path(cmd, *env_list);
	if (!target_path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target_path) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		perror("minishell: cd: getcwd");
		free(old_pwd);
		return (1);
	}
	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", current_pwd);
	return (0);
}
