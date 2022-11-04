SRCS =	src/main.c \
	src/utils.c

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

LIBFT = libft/libft.a

NAME = philosophers

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $(<:.c=.o)

$(LIBFT) :
	make -C libft/

$(NAME) : compiling $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) -Llibft -lft  -o $(NAME)
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
	make -C libft/ fclean
	@echo "\033[m🧹 $(NAME) binary files cleaned!\033[0m"

fclean : clean
	rm -rf $(NAME)
	@echo "\e[1A\e[1m🧹 $(NAME) binary files and executable cleaned!\033[0m"

re : fclean all
	@echo "\e[5A\e[1m🗜️  $(NAME) has been ReMake\e[1;5m!                    \033[0m"

.PHONY : all re clean fclean
.SILENT :