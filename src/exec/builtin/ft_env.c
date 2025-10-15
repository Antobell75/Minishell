/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwsasd <dwsasd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:02:07 by anbellar          #+#    #+#             */
/*   Updated: 2025/10/15 16:08:17 by dwsasd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_var *env)
{
	if (!env)
		return (0); // Pas une erreur, juste rien à afficher
	while (env) // <-- FIX: La condition inclut le dernier élément
	{
		// Bash n'affiche que les variables qui ont une valeur
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}