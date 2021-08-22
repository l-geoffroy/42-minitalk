/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:03:35 by lgeoffro          #+#    #+#             */
/*   Updated: 2021/08/22 15:06:29 by lgeoffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <assert.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"

typedef struct s_siginfo {
	int	server_pid;
}	t_siginfo;

char	*ft_ascii_to_bin(char *s);
void	send_bin(char *binstr, int pid);
int		sender_core(char **argv);

#endif
