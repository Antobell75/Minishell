/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:18:49 by anbellar          #+#    #+#             */
/*   Updated: 2025/07/28 12:18:49 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd[0] == NULL)
	{
		free(s_cmd);
		ft_error("split");
	}
	path = NULL;
	if (access(s_cmd[0], F_OK & X_OK) == 0)
		path = ft_strdup(s_cmd[0]);
	else
		path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_free_tab(s_cmd);
		ft_error("pipex: env not found\n");
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_tab(s_cmd);
		free(path);
		ft_error("pipex: command not found\n");
	}
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	size_t	len;
	
	(void)argc;
	(void)argv;
	while (1)
	{
		input = NULL;
		len = 0;
		printf(">>> ");
		if (getline(&input, &len, stdin) == -1)
		{
			perror("getline");
			free(input);
			break;
		}
		if (input[0] == '\n')
		{
			free(input);
			continue;
		}
		else
		{
			exec(input, env);
			free(input);
		}
	}
	return (0);
}
