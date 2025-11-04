/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:39:18 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/22 04:58:31 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*new_s;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_s = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!new_s)
		return (0);
	ft_strlcpy(new_s, s1, len_s1 + 1);
	ft_strlcat(new_s, s2, len_s1 + len_s2 + 1);
	return (new_s);
}
