# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 16:21:12 by lgeoffro          #+#    #+#              #
#    Updated: 2021/08/21 11:55:43 by lgeoffro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I includes/

SERVER_SRC:= server/server.c \
			 server/utils.c \

SERVER = server/server

CLIENT_SRC = client/client.c \

CLIENT = client/client

LIB = libft.a
LIB_NAME = ft
LIB_DIR = libft/

INCLUDE_DIR = includes

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

RM = rm -f

all: $(LIB) $(SERVER) $(CLIENT)
	
$(LIB):
	make -C $(LIB_DIR)

$(SERVER): $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) -L $(LIB_DIR) -l $(LIB_NAME) -g3 -fsanitize=address

$(CLIENT): $(CLIENT_OBJ)
	$(CC) -o $(CLIENT) $(CLIENT_OBJ) -L $(LIB_DIR) -l $(LIB_NAME)

clean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
	make -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
