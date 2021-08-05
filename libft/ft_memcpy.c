/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:50:03 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/07/09 15:28:28 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_mem;
	unsigned char	*s_mem;

	i = 0;
	if (dst || src)
	{
		d_mem = (unsigned char *)dst;
		s_mem = (unsigned char *)src;
		while (i < n)
		{
			d_mem[i] = s_mem[i];
			i++;
		}
		return (dst);
	}
	return (NULL);
}
