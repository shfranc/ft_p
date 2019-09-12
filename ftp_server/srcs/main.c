#include "server.h"

static void			usage(char *prog_name)
{
	printf("%s: port\n", prog_name);
	exit(1);
}

static t_ex_ret		init_server(char *port_str)
{
	char	**lvl;

	ft_bzero(&g_server, sizeof(g_server));
	g_server.family = IP_V4;
	if (!(g_server.root_dir = getcwd(NULL, 0)))
		return (ret_failure(ROOT_ERR));
	if (ft_strchr(g_server.root_dir, '\\'))
	{
		free(g_server.root_dir);
		return (ret_failure(ROOT_ERR_1));
	}
	lvl = ft_strsplit(g_server.root_dir, '/');
	g_server.tree_lvl = ft_tablen(lvl);
	ft_freetab(&lvl);
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
	log_info_str("Protocol", (g_server.family == IP_V6 ? "ipv6" : "ipv4"));
	log_info_nbr("Port", g_server.port);
	log_info_str("Root", g_server.root_dir);
	log_info_nbr("Level", g_server.tree_lvl);
	handle_clients(g_server.server_sock);
	return (close_server(SUCCESS));
}
