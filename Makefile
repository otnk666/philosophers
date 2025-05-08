NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS_DIR	= ./srcs
INC_DIR		= ./includes

RM		= rm -r

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
