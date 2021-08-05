/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:30 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/07/09 13:52:04 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nb)
{
	if (nb < 0)
		return (ft_intlen(-nb) + 1);
	if (nb >= 10)
		return (ft_intlen(nb / 10) + 1);
	return (1);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	len;

	len = ft_intlen(n) + 1;
	num = (char *)malloc(sizeof(char) * len);
	if (!num)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(num, "-2147483648"));
	num[--len] = '\0';
	if (n < 0)
	{
		n *= -1;
		num[0] = '-';
	}
	if (n == 0)
		return (ft_strcpy(num, "0"));
	while (len && n)
	{
		num[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (num);
}
