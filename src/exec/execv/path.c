/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:55:24 by dwsasd            #+#    #+#             */
/*   Updated: 2025/10/15 16:48:07 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_path(char *path_dir, char *cmd)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(path_dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path_dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

static char	*search_in_paths(char **path_dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = join_path(path_dirs[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_var *env_list)
{
	char	**path_dirs;
	char	*path_value;
	char	*found_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path_value = get_env_value("PATH", env_list);
	if (!path_value)
		return (NULL);
	path_dirs = ft_split(path_value, ':');
	if (!path_dirs)
		return (NULL);
	found_path = search_in_paths(path_dirs, cmd);
	free_split(path_dirs);
	return (found_path);
}
