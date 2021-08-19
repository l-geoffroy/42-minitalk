#define _POSIX_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1
#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h> //remove
#include "libft.h"

void	sig_handler(int sig);