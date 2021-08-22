/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:03:38 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:06:04 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define _POSIX_SOURCE
# define _XOPEN_SOURCE_EXTENDED 1
# include <assert.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

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
void	add_sender(t_list *sig_lst, int pid);
int		is_active_pid(t_list *sig_lst, int pid);
int		is_len_set(t_list *sig_lst, int pid);
void	add_bit_len(t_list *sig_lst, int pid, int r_bit);
void	set_str_len(t_list *sig_lst, int pid);
void	memcpy_bit(char	*dst, char *src, int len);
int		bin_to_dec(int bnum);
int		add_bit(t_list *sig_lst, int pid, int r_bit);
void	print_message(t_list *sig_lst, int pid);
int		reset_pid(t_list *sig_lst);
void	ralloc_bit_len(t_list *tmp_lst, int r_bit);
void	free_node(t_list *tmp_lst, t_list *sig_lst, t_list *prev_node);
int		convert_bit_len(t_list *tmp_lst);

#endif
