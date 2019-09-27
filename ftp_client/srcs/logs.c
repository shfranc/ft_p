#include "client.h"

void			log_error(char *message)
{
	dprintf(STDERR_FILENO, "%s\t%s\n", LOG_ERROR, message);
}

void			log_client_command(char *cmd)
{
	printf("%s\t---> %s\n", LOG_CTRL, cmd);
}

void			log_server_response(char *cmd)
{
	printf("%s\t<--- %s\n", LOG_CTRL, cmd);
}
