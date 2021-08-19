/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 04:48:30 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/19 23:46:46 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

void	put_bin(int r_bit)
{
	static char	bit[9];
	static int	i = 0;

	bit[8] = 0;
	bit[i] = ('0' + r_bit);
	i++;
	if (i > 7)
	{
		ft_putchar(bin_to_dec(ft_atoi(bit)));
		i = 0;
	}
}

void	ft_sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGUSR1)
		ft_putstr("0");
	else if (sig == SIGUSR2)
		ft_putstr("1");
	(void)siginfo;
	(void)context;
}

int	main(int argc, char **argv)
{
	struct sigaction info;

	memset (&info, '\0', sizeof(info));
	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");

	info.sa_sigaction = &ft_sig_handler;

	info.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &info, NULL);
	sigaction(SIGUSR2, &info, NULL);
	while (1)
		pause();
	(void)argv;
	(void)argc;
	return (0);
}
