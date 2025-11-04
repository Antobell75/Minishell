/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:35:33 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/19 19:46:52 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;

	if (size && nmemb > 2147483647 / size)
		return (0);
	src = malloc(nmemb * size);
	if (!src)
		return (0);
	ft_bzero(src, size * nmemb);
	return (src);
}
