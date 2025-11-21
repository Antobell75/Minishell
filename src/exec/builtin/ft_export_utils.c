/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:21:48 by anbellar          #+#    #+#             */
/*   Updated: 2025/11/21 01:52:14 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_name(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (-1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	err_export(char *name)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_varsize(t_var *env)
{
	int		i;
	t_var	*tmp;

	if (!env)
		return (0);
	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	dol_emp(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]))
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}
