#define _POSIX_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1
#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

typedef struct s_siginfo {
	int		sender_pid;
	int		str_len;
	int		current_bit;
	int		current_char;
	int		current_bit_len;
	int		nb_zero_bit_len;
	int		nb_zero_bit;
	char	*bit_len;
	char	**bit;
}	t_siginfo;

void	sig_handler(int sig);
t_list	*add_sender(t_list *sig_lst, int pid);
int		is_active_pid(t_list *sig_lst, int pid);
int		is_len_set(t_list *sig_lst, int pid);
void	add_bit_len(t_list *sig_lst, int pid, int r_bit);
void	set_str_len(t_list *sig_lst, int pid);
void	memcpy_bit(char	*dst, char *src, int len);
int		bin_to_dec(int bnum);
int		add_bit(t_list *sig_lst, int pid, int r_bit);
void	print_message(t_list *sig_lst, int pid);