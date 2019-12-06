#include "client.h"

static char		*get_localhost_addr(int family, char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
		return (family == IP_V4 ? "127.0.0.1" : "::1");
	else return (addr);
}

static void	usage(char *prog_name)
{
	printf("usage: %s: addr port\n", prog_name);
	exit(1);
}

static void		init_client(char *addr, char *port)
{
	ft_bzero(&g_client, sizeof(t_client));
	g_client.handcheck = FALSE;
	g_client.family = is_option_activated('6') ? IP_V6 : IP_V4;
	g_client.addr = get_localhost_addr(g_client.family, addr);
	g_client.port = ft_atoi(port);
	g_client.pass = AUTO;
	g_client.ctrl_sock = -1;
	g_client.server_dtp_sock = -1;
	g_client.data_sock = -1;
	g_client.cwd = ft_strdup("/");
	g_client.resp = NULL;
	log_info_msg("Protocol", (g_client.family == IP_V6 ? "ipv6" : "ipv4"));
	log_info_msg("Server Address", g_client.addr);
	log_info_nb("Server Port", g_client.port);
}

void	server_handcheck()
{
	printf("Connected to %s\n", g_client.addr);
	get_server_response();
	if (g_client.resp && ft_strncmp(g_client.resp, RESP_220, 3) == 0)
		g_client.handcheck = TRUE;
}

t_client 		g_client;
int 			g_flags;

int		main(int argc, char **argv)
{
	char	*prog_name;
	char	*addr;
	char	*port;

	prog_name = argv[0];
	if (argc < 3 || get_options(&argc, &argv))
		usage(prog_name);
	if (!argc)
		usage(prog_name);
	addr = *argv++;
	port = *argv;
	if (!addr || !port)
		usage(prog_name);
	init_client(addr, port);
	signal(SIGINT, handle_sigint);
	if ((g_client.ctrl_sock = connect_to_server(g_client.addr, g_client.port)) != -1)
		server_handcheck();
	else
		printf("Can't connect to %s\n", g_client.addr);
	get_user_input();
	return (close_ctrl_sock());
}
