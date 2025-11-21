/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:24:11 by esergeev          #+#    #+#             */
/*   Updated: 2025/11/21 01:28:53 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exp_ctx
{
	t_var	*env;
	int		status;
	int		*i;
	int		*in_dquote;
}	t_exp_ctx;

static char	*ft_expand_var(char *str, int *i, t_var *env, int status)
{
	char	*name;
	char	*val;
	int		start;

	if (str[*i + 1] == '?')
		return (*i += 2, ft_itoa(status));
	if (ft_isdigit(str[*i + 1]))
		return (*i += 2, ft_strdup(""));
	if (!str[*i + 1] || !(ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'))
		return ((*i)++, ft_strdup("$"));
	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	val = get_env_value(name, env);
	free(name);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

static char	*handle_single_quote(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i] == '$')
		(*i) += 2;
	else
		(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*get_next_ins(char *str, t_exp_ctx *ctx)
{
	int	*i;

	i = ctx->i;
	if (str[*i] == '"')
	{
		*(ctx->in_dquote) = !(*(ctx->in_dquote));
		return (ft_chrdup(str[(*i)++]));
	}
	if (str[*i] == '\\' && str[*i + 1] == '$')
		return (*i += 2, ft_strdup("$"));
	if (!(*(ctx->in_dquote)) && ((str[*i] == '$' && str[*i + 1] == '\'')
			|| str[*i] == '\''))
		return (handle_single_quote(str, i));
	if (str[*i] == '$')
	{
		if (!(*(ctx->in_dquote)) && str[*i + 1] == '"')
			return ((*i)++, ft_strdup(""));
		return (ft_expand_var(str, i, ctx->env, ctx->status));
	}
	return (ft_chrdup(str[(*i)++]));
}

static char	*append_str(char *res, char *ins)
{
	char	*tmp;

	tmp = res;
	res = ft_strjoin(res, ins);
	free(tmp);
	free(ins);
	return (res);
}

char	*ft_expand(char *str, t_var *env, int status)
{
	char		*res;
	char		*ins;
	int			i;
	int			q;
	t_exp_ctx	ctx;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	q = 0;
	ctx.env = env;
	ctx.status = status;
	ctx.i = &i;
	ctx.in_dquote = &q;
	while (res && str[i])
	{
		ins = get_next_ins(str, &ctx);
		if (!ins)
			return (free(res), NULL);
		res = append_str(res, ins);
	}
	return (res);
}
