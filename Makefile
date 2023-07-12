NAME = philo

SRC_DIR = ./src
VPATH = src:inc

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj

INCLUDES = -Iinc
CFLAGS = -Wall -Wextra -Werror -MMD -g

SRC = main.c mutex.c errors.c utils.c printing.c philos.c governor.c eatsleep.c dierepeat.c philo_run.c

DEP = $(OBJ:.o=.d)

####
all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
re: fclean all