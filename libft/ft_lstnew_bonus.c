/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 03:52:47 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/22 04:54:18 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elememt;

	elememt = (t_list *)malloc(sizeof(t_list));
	if (!elememt)
		return (NULL);
	elememt->content = content;
	elememt->next = NULL;
	return (elememt);
}
