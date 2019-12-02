#include "client.h"

void			log_info(char *message)
{
	printf("%s\t%s\n", LOG_INFO, message);
}

void			log_info_msg(char *desc, char *message)
{
	printf("%s\t%s: %s\n", LOG_INFO, desc, message);
}

void			log_info_nb(char *desc, int nb)
{
	printf("%s\t%s: %d\n", LOG_INFO, desc, nb);
}

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
