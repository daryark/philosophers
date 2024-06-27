GREEN = \033[0;32m
RE = \033[0m
NAME = ./philo
C_FLAGS = -Wall -Wextra -Werror -pthread

SRC = philo.c utils.c init.c clean.c
OBJ_F = obj/
SRC_F = src/
VPATH = $(SRC_F)
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $@ $^ $(C_FLAGS)
	@echo "$(GREEN)\n\n—————————✣ PHILOSOPHERS COMPILED ✣—————————\n$(RE)"

$(OBJ_F)%.o:%.c Makefile philo.h
	mkdir -p $(@D)
	cc -o $@ -c $< $(C_FLAGS) 

clean:
	rm -rf $(OBJ_F)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re