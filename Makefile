NAME	= minishell

SRC	= src/main.c \
      src/shell/path_manager.c \
	  src/shell/run_manager.c \

INC = inc
OBJ_DIR = obj
SRC_DIR = src
CC = clang
LIB = ./libft/libft.a
LIBFT = ./libft
CFLAGS = -Wall -Werror -Wextra
LIBFLAGS = -lreadline -ltermcap

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

all:
	@mkdir -p $(OBJ_DIR)
	@(make -C $(LIBFT))
	@$(MAKE) -s $(NAME)
	@mv src/*.o src/*/**.o $(OBJ_DIR)

$(NAME): $(OBJ)
	${CC} $(CFLAGS) $(OBJ) -I $(INC) -o $(NAME) $(LIB) $(LIBFLAGS) 
	@echo "\033[0;32m----------------------------------\033[0m"
	@echo "\033[0;32m| => $(NAME) well created ! <= |\033[0m"
	@echo "\033[0;32m----------------------------------\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@(make clean -C $(LIBFT))
	@echo "\033[0;31m=> $(NAME) obj deleted <=\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@(make fclean -C $(LIBFT))
	@echo "\033[0;31m=> $(NAME) deleted <=\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re