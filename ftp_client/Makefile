NAME = client
FLAGS = -Wall -Wextra -Werror
CC = gcc

LIB = libft.a
PATH_LIB = ../libft
PATH_SRCS = srcs
PATH_OBJS = objs

SRCS = $(addprefix $(PATH_SRCS)/,\
	main.c \
	client.c \
	server.c \
	input.c \
	cmd_ascii.c \
	cmd_bin.c \
	cmd_cd.c \
	cmd_eprt.c \
	cmd_epsv.c \
	cmd_get.c \
	cmd_help.c \
	cmd_ls.c \
	cmd_pass.c \
	cmd_pasv.c \
	cmd_port.c \
	cmd_put.c \
	cmd_pwd.c \
	cmd_quit.c \
	data_channel.c \
	reader.c \
	parse_response.c \
	logs.c \
	signals.c \
	options.c \
	utils.c \
	)
OBJS = $(SRCS:$(PATH_SRCS)/%.c=$(PATH_OBJS)/%.o)
INCS = incs $(PATH_LIB)/includes

RED = \033[01;31m
GREEN = \033[01;32m
YELLOW = \033[01;33m
BLUE = \033[01;34m
PINK = \033[01;35m
CYAN = \033[01;36m
WHITE = \033[01;37m
RESET = \033[00m

all: $(NAME)

$(NAME): $(PATH_LIB)/$(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)$@:$(RESET) OK"

$(PATH_LIB)/$(LIB):
	@make -C $(PATH_LIB)

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(INCS)
	@test -d $(PATH_OBJS) || mkdir $(PATH_OBJS)
	@$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I , $(INCS))
	@echo "$(YELLOW)compil:$(RESET) $@"

norm:
	@norminette $(PATH_SRCS) incs

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@echo "$(BLUE)clean:$(RESET) $(PATH_OBJS)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)clean:$(RESET) $(NAME)"

fclean_lib:
	@make fclean -C $(PATH_LIB)

fclean_all: fclean_lib fclean

re_with_lib: fclean_all all

re: fclean all
