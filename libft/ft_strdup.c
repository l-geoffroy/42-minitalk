/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 22:55:22 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/07/09 13:57:17 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*d;

	d = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!d)
		return (NULL);
	d = ft_strcpy(d, s1);
	return (d);
}
