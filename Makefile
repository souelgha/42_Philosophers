NAME = philo
FLAGS = -Wall -Wextra -Werror -g

#DIRECTORY
SRC_PATH = src/
OBJ_PATH = obj/

SRC = 	philo.c init_datas.c error_free_mngnt.c utils_fcts.c \
		parsing.c init_threads.c monitoring.c routine.c 


SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/


all : $(NAME)

$(NAME) : $(OBJS) 
		@cc $(CFLAGS) $(OBJS) -o $(NAME) -pthread
		@echo "$(GREEN) compilation ok $(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@if [ ! -e $(OBJ_PATH) ]; then\
		mkdir -p $(OBJ_PATH);\
	fi
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) 

clean :
		@rm -rf $(OBJ_PATH)
		@echo "$(CLEAR) $(BLUE) cleaned $(RESET)"


fclean : clean
		@rm -rf $(NAME)
		@echo "$(CLEAR) $(BLUE) fcleaned $(RESET)"

re : fclean all

.PHONY: all clean fclean re

	
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[38;5;97m
CLEAR = \033[2J\033[H
RESET = \033[0m