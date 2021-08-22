/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:00:42 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:02:51 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ralloc_bit_len(t_list *tmp_lst, int r_bit)
{
	char	*tmp_bit_len;

	tmp_bit_len = (char *)malloc(sizeof(char)
			* ((t_siginfo *)tmp_lst->content)->current_bit_len);
	ft_memcpy(tmp_bit_len, ((t_siginfo *)tmp_lst->content)->bit_len,
		((t_siginfo *)tmp_lst->content)->current_bit_len);
	free(((t_siginfo *)tmp_lst->content)->bit_len);
	((t_siginfo *)tmp_lst->content)->bit_len = (char *)malloc(sizeof(char)
			* ((t_siginfo *)tmp_lst->content)->current_bit_len);
	ft_memcpy(((t_siginfo *)tmp_lst->content)->bit_len, tmp_bit_len,
		((t_siginfo *)tmp_lst->content)->current_bit_len);
	((t_siginfo *)tmp_lst->content)->bit_len[
		((t_siginfo *)tmp_lst->content)->current_bit_len] = '0' + r_bit;
	((t_siginfo *)tmp_lst->content)->current_bit_len++;
	return ;
}

int	reset_pid(t_list *sig_lst)
{
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	if (tmp_lst->next == sig_lst)
		return (((t_siginfo *)tmp_lst->content)->sender_pid);
	while (tmp_lst->next == sig_lst)
		tmp_lst = tmp_lst->next;
	return (((t_siginfo *)tmp_lst->content)->sender_pid);
}

void	print_message(t_list *sig_lst, int pid)
{
	t_list	*tmp_lst;
	t_list	*prev_node;
	int		i;

	tmp_lst = sig_lst;
	i = 0;
	if (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
	{
		while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		{
			prev_node = tmp_lst;
			tmp_lst = tmp_lst->next;
		}
	}
	else
		prev_node = tmp_lst;
	while (i < ((t_siginfo *)tmp_lst->content)->str_len - 1)
	{
		ft_putchar(bin_to_dec(ft_atoi(
					((t_siginfo *)tmp_lst->content)->bit[i])));
		i++;
	}
	ft_putstr("\n[ACK CLIENT]\n\n");
	free_node(tmp_lst, sig_lst, prev_node);
}

void	free_node(t_list *tmp_lst, t_list *sig_lst, t_list *prev_node)
{
	free(((t_siginfo *)tmp_lst->content)->bit);
	free(((t_siginfo *)tmp_lst->content)->bit_len);
	free(((t_siginfo *)tmp_lst->content));
	if (tmp_lst->next == sig_lst && tmp_lst == sig_lst)
		prev_node->next = sig_lst;
	else
		prev_node->next = tmp_lst->next;
	free(tmp_lst);
}

int	is_len_set(t_list *sig_lst, int pid)
{
	int		is_set;
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	is_set = 0;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	if (((t_siginfo *)tmp_lst->content)->str_len == -1)
		return (0);
	return (1);
}
