# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 09:08:37 by rstride           #+#    #+#              #
#    Updated: 2025/12/23 09:12:23 by rstride          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ping

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= srcs
INC_DIR		= includes
OBJ_DIR		= objs

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/args.c \
			  $(SRC_DIR)/resolve.c \
			  $(SRC_DIR)/socket.c \
			  $(SRC_DIR)/icmp.c \
			  $(SRC_DIR)/checksum.c \
			  $(SRC_DIR)/ping.c \
			  $(SRC_DIR)/display.c \
			  $(SRC_DIR)/stats.c \
			  $(SRC_DIR)/error.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/ft_ping.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
