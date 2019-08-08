#include "server.h"

void	handle_sigint(int sig)
{
	(void)sig;
	exit(close_server(FAILURE));
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}
