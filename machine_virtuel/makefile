NAME 						= corewar

CC							= gcc

C_DIR 						= srcs/
C_PARSING_DIR 				= srcs/parsing/
C_FUNC_ERROR 				= srcs/func_error/
C_CURSE_DIR 				= srcs/ncurse/
C_GAME_DIR 					= srcs/game/
C_ATTACKFUNC_DIR 			= srcs/function/

O_DIR 						= o/
LIBFT 						= ../libft/

H_DIR 						= -I ./includes/
LIBS_H_DIR					= -I ../libft/includes/

FLAGS =  -Wall -Werror -Wextra
INCURSES = -lncurses
LINKS = $(H_DIR) $(LIBS_H_DIR)
C_FILES = main.c print_dump.c vm_error.c add.c aff.c and.c \
check_function.c fork.c ld.c ldi.c lfork.c live.c lld.c lldi.c or.c \
st_func.c sti.c sub.c xor.c zjump.c \
function.c game.c key_hook.c op.c put_player_in_memory.c put_process.c \
write_from.c display.c display_window.c init_color.c init_memory.c \
manage_display.c memory_fight.c n_curse.c get_parsing.c \
hexa_to_binary.c hexa_to_decimal.c parsing.c read_champion_infos.c \
read_instruction.c reading_file.c

O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all:
	@make -C $(LIBFT)
	@make -j4 $(NAME)

$(NAME): $(O_FILES)
	@$(CC) -O3 $(CFLAGS) $(LIBS) $(H_DIR) $(O_FILES) $(FT_O) $(INCURSES) -L../libft -lft -o $(NAME) && printf "\033[0;32m" || printf "\033[0;31m"
	@echo -e "\033[1;32m"
	@echo ""
	@echo "_____"
	@echo "/ ____|"
	@echo "| |     ___  _ __ _____      ____ _ _ __ "
	@echo "| |    / _ \| '__/ _ \ \ /\ / / _\` | '__|"
	@echo "| |___| (_) | | |  __/\ V  V / (_| | |"
	@echo "\_____\___/|_|  \___| \_/\_/ \__,_|_|"
	@printf "%-24s\033[1;30m<<--\033[0;0m\n" "$@"

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(C_PARSING_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(C_FUNC_ERROR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(C_CURSE_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(C_GAME_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(C_ATTACKFUNC_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)
clean:
	@rm $(O_FILES) $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@rmdir -p $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) clean

fclean: clean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) fclean

re: fclean all

print-%  : ; @echo $* = $($*)
.PHONY: all clean fclean re
