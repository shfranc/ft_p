#include "server.h"

void			usage(char *prog_name)
{
	printf("%s: port\n", prog_name);
	exit(1);
}

int 			g_server_sock = -1;

int				main(int argc, char **argv)
{
	uint16_t				port;

	if (argc != 2)
		usage(argv[0]);
	if (!(port = get_port(argv[1])))
		return (FAILURE);
	if ((g_server_sock = create_server(port)) == -1)
		return (FAILURE);
	signal(SIGINT, handle_sigint);
	if (handle_clients(g_server_sock) == FAILURE)
		return (close_server(FAILURE));
	return (close_server(SUCCESS));
}
