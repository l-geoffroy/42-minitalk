/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:00:29 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:00:30 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*ft_ascii_to_bin(char *s)
{
	size_t	i;
	char	*binary;
	int		j;
	char	ch;

	if (s == NULL)
		return (0);
	binary = malloc(ft_strlen(s) * 8 + 1);
	i = 0;
	while (i < ft_strlen(s))
	{
		ch = s[i];
		j = 7;
		while (j >= 0)
		{
			if (ch & (1 << j))
				ft_strcat(binary, "1");
			else
				ft_strcat(binary, "0");
			j--;
		}
		i++;
	}
	return (binary);
}

void	send_bin(char *binstr, int pid)
{
	int	binstr_len;
	int	i;

	binstr_len = ft_strlen(binstr);
	i = 0;
	while (i < binstr_len)
	{
		if (binstr[i] == '1')
			kill(pid, SIGUSR2);
		else if (binstr[i] == '0')
			kill(pid, SIGUSR1);
		usleep(300);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(1000);
		i++;
	}
}
