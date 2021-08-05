#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"

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
		usleep(50);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*bin;

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
	bin = ft_ascii_to_bin(argv[2]);
	send_bin(bin, ft_atoi(argv[1]));
	free(bin);
	return (0);
}
