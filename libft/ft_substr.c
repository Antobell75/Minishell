/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:34:57 by sle-bail          #+#    #+#             */
/*   Updated: 2024/11/22 08:31:50 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				index;
	int				i;
	size_t			len_s;
	char			*new_s;
	unsigned int	slen;

	slen = ft_strlen(s);
	i = 0;
	index = 0;
	len_s = 0;
	if (start >= slen)
		start = slen;
	if (len > slen - start)
		len = slen - start;
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (0);
	ft_strlcpy(new_s, s + start, len + 1);
	return (new_s);
}
