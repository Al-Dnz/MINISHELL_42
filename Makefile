NAME	= minishell

SRC	= main.c \
	  run_manager.c \
	  print_error.c \
	  check_syntax.c \
	  check_syntax_redir.c \
	  check_suit.c \
	  right_char.c \
	  size_util.c \
	  get_token.c \
	  arg_util.c \
	  fd_list_util.c \
	  redir_util.c \
	  hdoc_util.c \
	  btree_util.c \
	  display.c \
	  tree_constructor.c \
	  tree_constructor_util.c \
	  token_cleaner.c \
	  ft_strextend.c \
	  set_node_arr.c \
	  set_node_hdoc.c \
	  path_manager.c \
	  free_prog.c \
	  clean_prog.c \
	  cmd_execution.c \
	  redir_execution.c \
	  tree_execution.c \
	  pipe_hdoc.c \
	  pipe_hdoc_util.c \
	  launch_pipe_hdoc.c \
	  signal_handler.c \
	  signal_handler2.c \
	  set_env.c \
	  env_utils.c \
	  echo.c \
	  env.c \
	  exit.c \
	  pwd.c \
	  cd.c \
	  export.c \
	  unset.c \
	  builtins_utils.c \

INC = inc
OBJ_DIR = obj
SRC_DIR = src
LIB = ./libft/libft.a
LIBFT = ./libft
CFLAGS = -Wall -Werror -Wextra# -g -fsanitize=address
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	CC = clang
	LIBFLAG = -lreadline -L/usr/lib/x86-64-linux-gnu -ltermcap 
	INCFLAG = -I/usr/include
endif
ifeq ($(UNAME), Darwin)
	CC = cc
#	LIBFLAG = -lreadline  -L/usr/local/opt/readline/lib -ltermcap 
	LIBFLAG = -lreadline -ltermcap 
	INCFLAG = -I/usr/local/opt/readline/include
endif

SRC_FOLDERS = $(shell find $(SRC_DIR) -type d)
vpath %.c $(foreach dir, $(SRC_FOLDERS), $(dir))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

all:
	@mkdir -p $(OBJ_DIR)
	@(make -C $(LIBFT))
	@(make  $(NAME))

$(NAME): $(OBJ)
	${CC} $(CFLAGS) $(OBJ) -I $(INC) -o $(NAME) $(LIB) $(LIBFLAG) $(INCFLAG) 
	@echo "\033[0;32m----------------------------------\033[0m"
	@echo "\033[0;32m| => $(NAME) well created ! <= |\033[0m"
	@echo "\033[0;32m----------------------------------\033[0m"

$(OBJ_DIR)/%.o : %.c
	${CC} $(CFLAGS) -I $(INC) -c $< -o $@

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