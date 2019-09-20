#include "server.h"

void	handle_sigint(int sig)
{
	(void)sig;
	close_server();
	exit(FAILURE);
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}
