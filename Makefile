SRCS =	main.c \
	utils.c \
	init.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_put.c

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -lpthread

NAME = philosophers

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME) : compiling $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "\033[1;32m📦 $(NAME) compiled!\033[0m"
	@echo "\e[1m   <+><+><+><+><+>\033[0m"

commit :
	git add *
	git commit -m "Update"

compiling :
	@echo "\e[1m   <+><+><+><+><+>\033[0m"
	@echo "\e[1;5m🗜️  $(NAME) compiling...\033[0m"

clean :
	rm -f $(OBJS)
	@echo "\033[m🧹 $(NAME) binary files cleaned!\033[0m"

fclean : clean
	rm -rf $(NAME)
	@echo "\e[1A\e[1m🧹 $(NAME) binary files and executable cleaned!\033[0m"

re : fclean all
	@echo "\e[5A\e[1m🗜️  $(NAME) has been ReMake\e[1;5m!                    \033[0m"

.PHONY : all re clean fclean
.SILENT :