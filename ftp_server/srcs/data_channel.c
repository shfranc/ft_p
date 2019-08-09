#include "server.h"

void		extended_passive_mode(int client_sock)
{
	int		data_sock;
	int		dtp_port;

	srand(time(NULL));
	dtp_port = rand() % USHRT_MAX + 1023;
	while ((data_sock = create_server(dtp_port)) == -1)
		dtp_port = rand() % USHRT_MAX + 1023;

	dprintf(client_sock, "PORT %d\r\n", data_sock);
}

void		passive_mode(int client_sock)
{
	(void)client_sock;
}

