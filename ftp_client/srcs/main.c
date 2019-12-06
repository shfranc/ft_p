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
	ft_bzero(&g_client, sizeof(g_client));
	g_client.handcheck = FALSE;
	g_client.family = IP_V6;
	g_client.addr = get_localhost_addr(g_client.family, addr);
	g_client.port = ft_atoi(port);
	g_client.pass = AUTO;
	g_client.ctrl_sock = -1;
	g_client.server_dtp_sock = -1;
	g_client.data_sock = -1;
	g_client.cwd = ft_strdup("/");
	g_client.resp = NULL;
}

void	server_handcheck()
{
	printf("Connected to %s\n", g_client.addr);
	get_server_response();
	if (g_client.resp && ft_strncmp(g_client.resp, RESP_220, 3) == 0)
		g_client.handcheck = TRUE;
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		usage(argv[0]);
	init_client(argv[1], argv[2]);
	signal(SIGINT, handle_sigint);
	if ((g_client.ctrl_sock = connect_to_server(g_client.addr, g_client.port)) != -1)
		server_handcheck();
	else
		printf("Can't connect to %s\n", g_client.addr);
	get_user_input();
	return (close_ctrl_sock());
}
