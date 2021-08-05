/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 10:19:52 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/07/09 13:57:41 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	s_size;

	if (src && dst)
	{
		s_size = ft_strlen(src);
		if (dstsize > 0)
		{
			if (s_size < dstsize - 1)
				ft_memcpy(dst, src, s_size + 1);
			else
			{
				ft_memcpy(dst, src, dstsize - 1);
				dst[dstsize - 1] = '\0';
			}
		}
		return (s_size);
	}
	return (0);
}
