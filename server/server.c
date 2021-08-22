/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 04:48:30 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:00:47 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_list	*g_sig_lst;

int	bin_to_dec(int bnum)
{
	int	n;
	int	digit;
	int	dec;
	int	i;

	dec = 0;
	i = 0;
	n = bnum;
	while (n != 0)
	{
		digit = n % 10;
		dec += digit << i;
		n = n / 10;
		i++;
	}
	return (dec);
}

void	put_bin(int r_bit, long int sender_pid)
{
	if (sender_pid == 0)
		sender_pid = (long int)reset_pid(g_sig_lst);
	if (is_active_pid(g_sig_lst, sender_pid) == 0)
		add_sender(g_sig_lst, sender_pid);
	if (is_len_set(g_sig_lst, sender_pid) == 0)
		add_bit_len(g_sig_lst, sender_pid, r_bit);
	else
	{
		if (add_bit(g_sig_lst, sender_pid, r_bit) == 1)
		{
			print_message(g_sig_lst, sender_pid);
			kill(sender_pid, SIGUSR2);
		}
	}
}

void	ft_sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGUSR1)
		put_bin(0, (long)siginfo->si_pid);
	else if (sig == SIGUSR2)
		put_bin(1, (long)siginfo->si_pid);
	(void)context;
}

int	main(int argc, char **argv)
{
	struct sigaction	info;

	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	g_sig_lst = (t_list *)malloc(sizeof(t_list));
	g_sig_lst->next = g_sig_lst;
	g_sig_lst->content = (t_siginfo *)malloc(sizeof(t_siginfo));
	((t_siginfo *)g_sig_lst->content)->sender_pid = -1;
	info.sa_sigaction = &ft_sig_handler;
	info.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &info, NULL);
		sigaction(SIGUSR2, &info, NULL);
	}
	(void)argv;
	(void)argc;
	return (0);
}
