/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:06:49 by sle-bail          #+#    #+#             */
/*   Updated: 2025/10/15 17:57:53 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define WORD 0
# define REDIR_IN 1			// <
# define REDIR_OUT 2		// >
# define REDIR_APPEND 3		// >>
# define HEREDOC 4			// <<
# define PIPE 5				// |

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct s_redirect
{
	int		type;
	int		is_heredoc;
	char	*files;
	char	*eof;
}	t_redirect;

typedef struct s_cmd
{
	char			**cmd;
	int				nb_redirect;
	t_redirect		*redirect;
	int				*infile;
	int				outfile;
	int				code;
	struct s_cmd	*next;
}	t_cmd;

/* PARSING & SETUP */
t_cmd	*cmd_new(char **argv, int *infile_fd, int outfile_fd);
// Ajoute ici tes autres prototypes de parsing...

/* EXECUTION */
int		execute_pipeline(t_cmd *cmd_list, t_var **env_list, int last_status);
int		run_single_cmd(t_cmd *cmd, t_var **env_list, int last_status);

/* PROCESS MANAGEMENT */
void		exec_external_cmd(t_cmd *cmd, t_var **env_list);

/* BUILTINS */
int		is_builtin(char *cmd_name);
int		exec_builtin(t_cmd *cmd, t_var **env_list, int last_status);
int		ft_cd(t_cmd *cmd, t_var **env_list);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_var *env);
int		ft_exit(t_cmd *cmd, int last_status);
int		ft_export(t_cmd *cmd, t_var **env_list);
int		ft_pwd(void);
int		ft_unset(t_cmd *cmd, t_var **env_list);

/* REDIRECTIONS */
int		apply_redirections(t_cmd *cmd);
void	restore_fds(int original_stdin, int original_stdout);

/* ENVIRONMENT & PATH */
t_var	*create_env(char **envp);
t_var	*new_var(char *envp_line);
char	**convert_env_list(t_var *list);
char	*get_env_value(char *name, t_var *env_list);
char	*find_cmd_path(char *cmd, t_var *env_list);

/* UTILS & MEMORY */
void	free_split(char **tab);
void	*free_env(t_var *env);
void	cmd_free(t_cmd *c);
void	free_cmd_list(t_cmd *list);
int		ft_strcmp(const char *s1, const char *s2);
int		err_msg(const char *pfx, const char *msg, int code);

#endif