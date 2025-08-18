# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 15:41:54 by skomatsu          #+#    #+#              #
#    Updated: 2025/08/13 15:50:25 by skomatsu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
SRCS_DIR	= ./srcs
UTILI_DIR	= ./srcs/utili
INC_DIR		= ./includes

RM		= rm -f

SRCS =	$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/init.c \
		$(SRCS_DIR)/init_table.c \
		$(SRCS_DIR)/monitor.c \
		$(SRCS_DIR)/philo.c \
		$(SRCS_DIR)/philo_eat.c \
		$(SRCS_DIR)/check.c \
		$(SRCS_DIR)/clean.c \
		$(SRCS_DIR)/error.c \
		$(UTILI_DIR)/utili.c \
		$(UTILI_DIR)/ft_atoi.c \
		$(UTILI_DIR)/ft_fputs.c \
		$(UTILI_DIR)/ft_usleep.c


OBJS = $(SRCS:.c=.o)
INCLUDES = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
.c.o :
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME) 5 800 200 200
	./$(NAME) 4 410 200 200
	./$(NAME) 1 800 200 200

valgrind: $(NAME)


.PHONY : all clean fclean re test 