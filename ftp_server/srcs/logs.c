#include "server.h"

void			log_info(char *message)
{
	printf("%s\t%s\n", LOG_INFO, message);
}

void			log_info_nbr(char *message, int nb)
{
	printf("%s\t%s: %d\n", LOG_INFO, message, nb);
}

void			log_info_str(char *desc, char *message)
{
	printf("%s\t%s: %s\n", LOG_INFO, desc, message);
}

void			log_client_command(char *cmd)
{
	printf("%s\t<--- %s\n", LOG_CTRL, cmd);
}

void			log_server_response(char *cmd)
{
	printf("%s\t---> %s\n", LOG_CTRL, cmd);
}

void			log_data_str(char *desc, char *message)
{
	printf("%s\t%s: %s\n", LOG_DATA, desc, message);
}
