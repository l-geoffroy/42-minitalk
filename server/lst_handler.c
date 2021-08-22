/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 02:23:56 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:09:10 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	is_active_pid(t_list *sig_lst, int pid)
{
	int		is_new;
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	is_new = 0;
	while (tmp_lst != sig_lst)
	{
		if (((t_siginfo *)tmp_lst->content)->sender_pid == pid)
			is_new = 1;
		tmp_lst = tmp_lst->next;
	}
	return (is_new);
}

void	add_sender(t_list *sig_lst, int pid)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	tmp->content = (t_siginfo *)malloc(sizeof(t_siginfo));
	((t_siginfo *)tmp->content)->bit_len = (char *)malloc(1);
	((t_siginfo *)tmp->content)->sender_pid = pid;
	((t_siginfo *)tmp->content)->current_bit = 0;
	((t_siginfo *)tmp->content)->current_char = 0;
	((t_siginfo *)tmp->content)->current_bit_len = 0;
	((t_siginfo *)tmp->content)->nb_zero_bit_len = 0;
	((t_siginfo *)tmp->content)->nb_zero_bit = 0;
	((t_siginfo *)tmp->content)->str_len = -1;
	tmp->next = sig_lst->next;
	sig_lst->next = tmp;
	sig_lst = tmp;
}

void	add_bit_len(t_list *sig_lst, int pid, int r_bit)
{
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	if (((t_siginfo *)tmp_lst->content)->nb_zero_bit_len + 1 >= 8
		&& (((t_siginfo *)tmp_lst->content)->current_bit_len + 1) % 8 == 0)
	{
		set_str_len(sig_lst, pid);
		return ;
	}
	else
	{
		ralloc_bit_len(tmp_lst, r_bit);
		if (r_bit == 0)
			((t_siginfo *)tmp_lst->content)->nb_zero_bit_len++;
		else
			((t_siginfo *)tmp_lst->content)->nb_zero_bit_len = 0;
	}
}

int	add_bit(t_list *sig_lst, int pid, int r_bit)
{
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	if (r_bit == 0)
		((t_siginfo *)tmp_lst->content)->nb_zero_bit++;
	else
		((t_siginfo *)tmp_lst->content)->nb_zero_bit = 0;
	((t_siginfo *)tmp_lst->content)->bit[
		((t_siginfo *)tmp_lst->content)->current_char]
	[((t_siginfo *)tmp_lst->content)->current_bit] = '0' + r_bit;
	if (((t_siginfo *)tmp_lst->content)->nb_zero_bit >= 8)
		return (1);
	((t_siginfo *)tmp_lst->content)->current_bit++;
	if (((t_siginfo *)tmp_lst->content)->current_bit == 8)
	{
		((t_siginfo *)tmp_lst->content)->bit[
			((t_siginfo *)tmp_lst->content)->current_char][8] = 0;
		((t_siginfo *)tmp_lst->content)->current_bit = 0;
		((t_siginfo *)tmp_lst->content)->current_char++;
		((t_siginfo *)tmp_lst->content)->nb_zero_bit = 0;
	}
	return (0);
}	

void	set_str_len(t_list *sig_lst, int pid)
{
	t_list	*tmp_lst;
	int		i;
	int		final;

	tmp_lst = sig_lst->next;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	((t_siginfo *)tmp_lst->content)->bit_len[
		((t_siginfo *)tmp_lst->content)->current_bit_len - 7] = 0;
	i = 0;
	final = convert_bit_len(tmp_lst) + 1;
	((t_siginfo *)tmp_lst->content)->str_len = final;
	((t_siginfo *)tmp_lst->content)->bit
		= (char **)malloc(sizeof(char *) * final);
	while (i < ((t_siginfo *)tmp_lst->content)->str_len)
	{
		((t_siginfo *)tmp_lst->content)->bit[i]
			= (char *)malloc((sizeof('1') * 9));
		i++;
	}
}
