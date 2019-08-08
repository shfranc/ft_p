#include "client.h"

void	usage(char *prog_name)
{
	printf("usage: %s: addr port\n", prog_name);
	exit(1);
}

int		g_client_sock = -1;

int		main(int argc, char **argv)
{
	int					port;

	if (argc != 3)
		usage(argv[0]);
	port = ft_atoi(argv[2]);
	if ((g_client_sock = create_client(argv[1], port)) == -1)
		return (FAILURE);
	signal(SIGINT, handle_sigint);
	if (send_commands_to_server(g_client_sock) == -1)
	{
		close(g_client_sock);
		return (FAILURE);
	}
	close(g_client_sock);
	return (SUCCESS);
}
