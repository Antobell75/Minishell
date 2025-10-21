#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	check_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		if (str[i] == quote)
			return (i + 1);
		return (printf("syntax error: unclosed quote\n"), -1);
	}
	return (0);
}

int	get_token_len(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '|')
		return (1);
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (2);
		return (1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		return (1);
	}
	if (str[i] == '"' || str[i] == '\'')
		return (check_quote(str));
	while (str[i] && !is_whitespace(str[i]) && !is_special(str[i]))
		i++;
	return (i);
}

char *extract_quoted(char *str, int len)
{
	char *result;
	int i;
	int j;

	if (str[0] != '\"' && str[0] != '\'')
		return (ft_substr(str, 0, len));
	result = malloc(sizeof(char) * (len - 1));
	if (!result)
		return (NULL);
	i = 1;
	j = 0;
	while (i < len - 1)
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}



