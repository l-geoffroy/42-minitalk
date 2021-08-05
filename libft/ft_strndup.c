/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:02:16 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/07/09 15:16:53 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*d;

	d = malloc(sizeof(char) * n + 1);
	if (d == NULL)
		return (NULL);
	d = ft_strncpy(d, s1, n);
	d[n] = '\0';
	return (d);
}
