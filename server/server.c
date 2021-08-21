/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 04:48:30 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/21 11:53:19 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_list *sig_lst;

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
	if (is_active_pid(sig_lst, sender_pid) == 0)
		sig_lst = add_sender(sig_lst, sender_pid);
	if (is_len_set(sig_lst, sender_pid) == 0)
		add_bit_len(sig_lst, sender_pid, r_bit);
	else
	{
		printf("[Received %d from %ld]\n", r_bit, sender_pid);
		if (add_bit(sig_lst, sender_pid, r_bit) == 1)
			print_message(sig_lst, sender_pid);
	}
	(void)r_bit;
	(void)sender_pid;
	(void)sig_lst;
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
	struct sigaction info;

	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");

	sig_lst = (t_list *)malloc(sizeof(t_list));
	sig_lst->next = sig_lst;
	sig_lst->content = (t_siginfo *)malloc(sizeof(t_siginfo));
	((t_siginfo *)sig_lst->content)->sender_pid = 0;
	info.sa_sigaction = &ft_sig_handler;
	info.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &info, NULL);
	sigaction(SIGUSR2, &info, NULL);
	while (1)
		pause();
	(void)argv;
	(void)argc;
	(void)info;
	return (0);
}
