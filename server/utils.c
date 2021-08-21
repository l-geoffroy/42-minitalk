/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 02:23:56 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/21 11:50:09 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		is_active_pid(t_list *sig_lst, int pid)
{
	int	is_new;
	t_list *tmp_lst;

	tmp_lst = sig_lst;
	is_new = 0;
	if (sig_lst != NULL)
	{
		tmp_lst = tmp_lst->next;
		while (tmp_lst != sig_lst)
		{
			if (((t_siginfo *)tmp_lst->content)->sender_pid == pid)
				is_new = 1;
			tmp_lst = tmp_lst->next;
		}
	}
	return (is_new);
}

t_list *add_sender(t_list *sig_lst, int pid)
{     
    t_list *tmp = (t_list *)malloc(sizeof(t_list));
 
	tmp->content = (t_siginfo *)malloc(sizeof(t_siginfo));
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
 
    return (sig_lst);
}

int		is_len_set(t_list *sig_lst, int pid)
{
	int		is_set;
	t_list	*tmp_lst;

	tmp_lst = sig_lst;
	is_set = 0;
	if (sig_lst != NULL)
	{
		tmp_lst = tmp_lst->next;
		while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
			tmp_lst = tmp_lst->next;
		if (((t_siginfo *)tmp_lst->content)->str_len == -1)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	add_bit_len(t_list *sig_lst, int pid, int r_bit)
{
	t_list	*tmp_lst;
	char	*tmp_bit_len;

	tmp_lst = sig_lst->next;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	/*printf("((t_siginfo *)tmp_lst->content)->current_bit_len + 1 : %d\n", ((t_siginfo *)tmp_lst->content)->current_bit_len + 1);
	printf("((t_siginfo *)tmp_lst->content)->current_bit_len %% 8 : %d\n", (((t_siginfo *)tmp_lst->content)->current_bit_len + 1) % 8);
	printf("((t_siginfo *)tmp_lst->content)->nb_zero_bit_len : %d\n", ((t_siginfo *)tmp_lst->content)->nb_zero_bit_len);*/
	if (((t_siginfo *)tmp_lst->content)->nb_zero_bit_len + 1 >= 8 && (((t_siginfo *)tmp_lst->content)->current_bit_len + 1) % 8 == 0)
	{
		set_str_len(sig_lst, pid);
		return ;
	}
	else
	{
		tmp_bit_len = (char *)malloc(sizeof(char) * ((t_siginfo *)tmp_lst->content)->current_bit_len);
		ft_memcpy(tmp_bit_len, ((t_siginfo *)tmp_lst->content)->bit_len, ((t_siginfo *)tmp_lst->content)->current_bit_len);
		free(((t_siginfo *)tmp_lst->content)->bit_len);
		((t_siginfo *)tmp_lst->content)->bit_len = (char *)malloc(sizeof(char) * ((t_siginfo *)tmp_lst->content)->current_bit_len);
		ft_memcpy(((t_siginfo *)tmp_lst->content)->bit_len, tmp_bit_len, ((t_siginfo *)tmp_lst->content)->current_bit_len);
		((t_siginfo *)tmp_lst->content)->bit_len[((t_siginfo *)tmp_lst->content)->current_bit_len] = '0' + r_bit;
		((t_siginfo *)tmp_lst->content)->current_bit_len++;
		if (r_bit == 0)
			((t_siginfo *)tmp_lst->content)->nb_zero_bit_len++;
		else
			((t_siginfo *)tmp_lst->content)->nb_zero_bit_len = 0;
	}
}

int		add_bit(t_list *sig_lst, int pid, int r_bit)
{
	t_list	*tmp_lst;

	tmp_lst = sig_lst->next;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	if (r_bit == 0)
		((t_siginfo *)tmp_lst->content)->nb_zero_bit++;
	else
		((t_siginfo *)tmp_lst->content)->nb_zero_bit = 0;
	if (((t_siginfo *)tmp_lst->content)->nb_zero_bit == 7)
		return (1);
	//printf("((t_siginfo *)tmp_lst->content)->current_char : %d\n((t_siginfo *)tmp_lst->content)->current_bit : %d\n", ((t_siginfo *)tmp_lst->content)->current_char, ((t_siginfo *)tmp_lst->content)->current_bit);
	((t_siginfo *)tmp_lst->content)->bit[((t_siginfo *)tmp_lst->content)->current_char][((t_siginfo *)tmp_lst->content)->current_bit] = '0' + r_bit;
	//printf("\t-> %c\n", ((t_siginfo *)tmp_lst->content)->bit[((t_siginfo *)tmp_lst->content)->current_char][((t_siginfo *)tmp_lst->content)->current_bit]);
	((t_siginfo *)tmp_lst->content)->current_bit++;
	if (((t_siginfo *)tmp_lst->content)->current_bit == 8)
	{
		((t_siginfo *)tmp_lst->content)->bit[((t_siginfo *)tmp_lst->content)->current_char][8] = 0;
		((t_siginfo *)tmp_lst->content)->current_bit = 0;
		((t_siginfo *)tmp_lst->content)->current_char++;
		((t_siginfo *)tmp_lst->content)->nb_zero_bit = 0;
	}
	return (0);
}

void	print_message(t_list *sig_lst, int pid)
{
	t_list	*tmp_lst;
	t_list	*prev_node;
	int		i;

	tmp_lst = sig_lst->next;
	i = 0;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
	{
		prev_node = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	while (i < ((t_siginfo *)tmp_lst->content)->str_len - 1)
	{
		ft_putchar(bin_to_dec(ft_atoi(((t_siginfo *)tmp_lst->content)->bit[i])));
		i++;
	}
	prev_node->next = tmp_lst->next;
	free(((t_siginfo *)tmp_lst->content)->bit);
	free(((t_siginfo *)tmp_lst->content)->bit_len);
	free(((t_siginfo *)tmp_lst->content));
	free(tmp_lst);
}	

void	set_str_len(t_list *sig_lst, int pid)
{
	t_list	*tmp_lst;
	int		i;
	int		j;
	int		final;
	char	tmp_bit[10];

	tmp_lst = sig_lst->next;
	i = 0;
	j = 0;
	final = 0;
	while (((t_siginfo *)tmp_lst->content)->sender_pid != pid)
		tmp_lst = tmp_lst->next;
	((t_siginfo *)tmp_lst->content)->bit_len[((t_siginfo *)tmp_lst->content)->current_bit_len - 7] = 0;
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
	i = 0;
	((t_siginfo *)tmp_lst->content)->str_len = final + 1;
	((t_siginfo *)tmp_lst->content)->bit = (char **)malloc(sizeof(char *) * (((t_siginfo *)tmp_lst->content)->str_len));
	while (i < ((t_siginfo *)tmp_lst->content)->str_len)
	{
		((t_siginfo *)tmp_lst->content)->bit[i] = (char *)malloc((sizeof(char) * 9));
		i++;
	}
	printf("Received string of len : %d from %d\n", ((t_siginfo *)tmp_lst->content)->str_len, pid);
}