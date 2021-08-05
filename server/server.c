#include <assert.h>
#include <signal.h>
#include <stdbool.h> /* false */
#include <stdio.h> /* perror */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/wait.h> /* wait, sleep */
#include <unistd.h> /* fork, write */
#include "libft.h"

void	sig_handler(int sig);

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

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		put_bin(0);
	else if (sig == SIGUSR2)
		put_bin(1);
}

int	main(int argc, char **argv)
{
	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
		pause();
	}
	(void)argv;
	(void)argc;
	return (0);
}
