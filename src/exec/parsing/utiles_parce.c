#include "minishell.h"

char *remove_quotes(char *str)
{
    int     len;
    char    *new_str;
    char    quote_char;
    int     i;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    quote_char = str[0];

    if (len >= 2 && (quote_char == '\"' || quote_char == '\'') && quote_char == str[len - 1])
    {
        new_str = (char *)malloc(sizeof(char) * (len - 1));
        if (!new_str)
            return (NULL);
        i = 0;
        while (i < len - 2)
        {
            new_str[i] = str[i + 1];
            i++;
        }
        new_str[i] = '\0';
        return (new_str);
    }
    return (ft_strdup(str));
}



static char	**realloc_args(char **cmd, char *value)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		new_arr[i] = cmd[i];
		i++;
	}
	new_arr[i] = ft_strdup(value);
	if (!new_arr[i])
	{
		free(new_arr);
		return (NULL);
	}
	new_arr[i + 1] = NULL;
	return (new_arr);
}


char	*ft_expand(char *str, t_var *env, int status)
{
	char	*expanded;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '?')
	{
		expanded = ft_itoa(status); 
		return (expanded);
	}
	while (env && ft_strcmp(env->name, str + 1) != 0)
		env = env->next;
	return (ft_strdup(env ? env->value : ""));
}

void	add_arg(t_cmd *new_cmd, char *value)
{
	char	**old;

	if (!new_cmd || !value)
		return ;
	old = new_cmd->cmd;
	new_cmd->cmd = realloc_args(new_cmd->cmd, value);
	if (!new_cmd->cmd)
	{
		new_cmd->cmd = old;
		return ;
	}
	if (old)
		free(old);
}


