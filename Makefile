#colors
RESET	= "\033[0m"
RED		= "\033[31m"
GREEN	= "\033[32m"

NAME := philo

SRCS := philo.c philo_utils.c init.c \
		parse.c philo_routine.c  monitor.c \
		lock_forks.c actions.c philo_utils2.c

OBJS := $(SRCS:.c=.o)
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo $(GREEN) "- Compiling FINISHED" $(RESET)

clean :
	@rm -f $(OBJS)
	@echo $(RED) " - Cleaned!" $(RESET)

fclean : clean
	@rm -f $(NAME)
	@echo $(RED) " - Full Cleaned!" $(RESET)

re : fclean all

.PHONY 	: clean
