NAME        = philo
B_NAME      = philo_bonus

SRC_FILES   = dinner_table.c init.c main.c philo_routine.c utils.c \
				utils2.c waiter_routine.c
B_SRC_FILES = dinner_table.c init.c main.c philo_routine.c routine_actions.c \
				utils.c waiter_routine.c

SRC         = $(addprefix mandatory/, $(SRC_FILES))
B_SRC       = $(addprefix bonus/, $(B_SRC_FILES))

PATH_OBJS   = objs

OBJ         = $(patsubst mandatory/%.c, $(PATH_OBJS)/%.o, $(SRC))
B_OBJ       = $(patsubst bonus/%.c, $(PATH_OBJS)/%.o, $(B_SRC))

CC          = cc
FLAGS       = -Wall -Wextra -Werror #-fsanitize=thread

RM          = rm -rf

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(PATH_OBJS)/%.o: mandatory/%.c
			@mkdir -p $(PATH_OBJS)
			@$(CC) $(FLAGS) -I includes/ -c $< -o $@

$(PATH_OBJS)/%.o: bonus/%.c
			@mkdir -p $(PATH_OBJS)
			@$(CC) $(FLAGS) -I includes/ -c $< -o $@

$(B_NAME):	$(B_OBJ)
			@$(CC) $(FLAGS) $(B_OBJ) -o $(B_NAME)


bonus:		$(B_NAME)

clean:
			@$(RM) $(PATH_OBJS)

fclean:		clean
			@$(RM) $(NAME) $(B_NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
