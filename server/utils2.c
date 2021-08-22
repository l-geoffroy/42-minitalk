/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:00:42 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:02:19 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	convert_bit_len(t_list *tmp_lst)
{
	int		i;
	int		j;
	int		final;
	char	tmp_bit[9];

	i = 0;
	j = 0;
	final = 0;
	while (i < ((t_siginfo *)tmp_lst->content)->current_bit_len - 7)
	{
		tmp_bit[j] = ((t_siginfo *)tmp_lst->content)->bit_len[i];
		if (j == 7)
		{
			tmp_bit[j + 1] = 0;
			final = (bin_to_dec(ft_atoi(tmp_bit)) - '0') + (final * 10);
			j = -1;
		}
		j++;
		i++;
	}
	return (final);
}
