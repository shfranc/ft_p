#include "client.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nExiting...\n");
	close(g_client.ctrl_sock);
	exit(FAILURE);
}
