#include "server.h"

static void			usage(char *prog_name)
{
	printf("%s: port\n", prog_name);
	exit(1);
}

static t_ex_ret		init_server(char *port_str)
{
	ft_bzero(&g_server, sizeof(g_server));
	if (!(g_server.root_dir = getcwd(NULL, 0)))
		return (ret_failure(ROOT_ERR));
	if (!(g_server.port = get_port(port_str)))
		return (FAILURE);
	return (SUCCESS);
}

t_server 		g_server;

int					main(int argc, char **argv)
{
	if (argc != 2)
		usage(argv[0]);
	if (init_server(argv[1]) == FAILURE)
		return (FAILURE);
	if ((g_server.server_sock = create_server(g_server.port)) == -1)
		return (FAILURE);
	signal(SIGINT, handle_sigint);
	log_info_str("Server root dir", g_server.root_dir);
	log_info_nbr("Server open on port", g_server.port);
	if (handle_clients(g_server.server_sock) == FAILURE)
		return (close_server(FAILURE));
	return (close_server(SUCCESS));
}
