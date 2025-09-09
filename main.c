/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:48 by anbellar          #+#    #+#             */
/*   Updated: 2025/09/09 18:53:33 by anbellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*rl;
	int		exit;

	exit = 0;
	while (exit != 1)
	{
		rl = readline(">");
		if (ft_strcmp(rl, "exit") == 0)
			break;
		if (ft_strcmp(rl, "pwd") == 0)
			getcwd(NULL, 0);
		printf("%s\n", rl);
	}
	return (0);
}
