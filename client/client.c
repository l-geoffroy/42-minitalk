#include "client.h"

void	ft_sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGUSR2)
	{
		ft_putstr("[Message successfully received]\n");
		exit(0);
	}
	(void)siginfo;
	(void)context;
}

int	sender_core(char **argv)
{
	char	*bin;
	char	*bin_len;
	int		str_len;
	int		client_pid;

	client_pid = getpid();
	bin = ft_ascii_to_bin(argv[2]);
	str_len = ft_strlen(argv[2]);
	bin_len = ft_ascii_to_bin(ft_itoa(str_len));
	usleep((client_pid % 100) * 5 + 123);
	send_bin(bin_len, ft_atoi(argv[1]));
	usleep(200);
	send_bin(bin, ft_atoi(argv[1]));
	free(bin);
	return (str_len);
}

int	main(int argc, char **argv)
{
	struct sigaction	info;
	int					timer_c;
	int					timer;

	if (argc != 3)
	{
		ft_putstr("Invalid arguments.\n");
		return (1);
	}
	if (kill(ft_atoi(argv[1]), 0) == -1)
	{
		ft_putstr("Invalid PID.\n");
		return (1);
	}
	timer_c = 0;
	info.sa_sigaction = &ft_sig_handler;
	info.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &info, NULL);
	timer = sender_core(argv) - 1;
	while (1 && timer_c++ < timer)
		usleep(20000);
	ft_putstr("[Request failed]\n");
	return (0);
}
