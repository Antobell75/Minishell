/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:18:22 by anbellar          #+#    #+#             */
/*   Updated: 2025/07/28 12:18:22 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

void	exec(char *cmd, char **env);
void	ft_free_tab(char **tab);
char	**get_env_path(char **envp);
char	*find_path(char *cmd, char **envp);
char	*get_path(char *cmd, char **env);
void	ft_error(char *str);
void	ft_free_tab(char **tab);

#endif