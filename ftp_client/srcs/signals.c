#include "client.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nExiting...\n");
	close(g_client_sock);
	exit(0);
}
