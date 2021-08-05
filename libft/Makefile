# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgeoffro <lgeoffro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 15:10:19 by lgeoffro          #+#    #+#              #
#    Updated: 2021/07/13 19:37:22 by lgeoffro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC :=  ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strcat.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_islower.c \
		ft_isspace.c \
		ft_isupper.c \
		ft_memccpy.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strndup.c \

SRC_BONUS := ft_lstadd_back.c \
			 ft_lstadd_front.c \
		 	 ft_lstclear.c \
			 ft_lstdelone.c \
			 ft_lstiter.c \
			 ft_lstlast.c \
			 ft_lstmap.c \
			 ft_lstnew.c \
			 ft_lstsize.c \
			 

OBJS := $(SRC:.c=.o)

OBJS_BONUS := $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(NAME) created successfully"

bonus: $(OBJS_BONUS)
	@ar rcs $(NAME) $(OBJS_BONUS)
	@echo "$(NAME) bonus functions created successfully"

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "All .o files sucessfully deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) sucessfully deleted"

re: fclean all

.PHONY: clean fclean re all bonus
