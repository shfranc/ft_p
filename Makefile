NAME = ft_p

PATH_SERVER = ftp_server/
SERVER = $(PATH_SERVER)server

PATH_CLIENT = ftp_client/
CLIENT = $(PATH_CLIENT)client

GIT_LIB = https://github.com/shfranc/libft
PATH_LIB = libft/
LIBFT = $(PATH_LIB)/libft.a

CYAN = \033[01;36m
RESET = \033[0m

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@if [ ! -d $(PATH_LIB) ] ; then \
		git clone $(GIT_LIB) $(PATH_LIB); \
	fi
	@make -C $(PATH_LIB)

$(SERVER):
	@printf "$(CYAN)%s$(RESET)\n" "============ server ============="
	@make -C $(PATH_SERVER)

$(CLIENT):
	@printf "$(CYAN)%s$(RESET)\n" "============ client ============="
	@make -C $(PATH_CLIENT)

norm:
	@make -C $(PATH_SERVER) norm
	@make -C $(PATH_CLIENT) norm

clean:
	@make -C $(PATH_SERVER) clean
	@make -C $(PATH_CLIENT) clean
	@make -C $(PATH_LIB) clean

fclean: clean
	@make -C $(PATH_SERVER) fclean
	@make -C $(PATH_CLIENT) fclean

fclean_lib:
	@make fclean -C $(PATH_LIB)

fclean_all: fclean_lib fclean

re_with_lib: fclean_all all

re: fclean all
