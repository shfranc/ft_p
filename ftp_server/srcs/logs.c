#include "server.h"

void			log_info(char *message)
{
	printf("[INFO]\t%s\n", message);
}

void			log_info_nbr(char *message, int nb)
{
	printf("[INFO]\t%s: %d\n", message, nb);
}

void			log_info_str(char *desc, char *message)
{
	printf("[INFO]\t%s: %s\n", desc, message);
}

void			log_client_command(char *cmd)
{
	printf("[CTRL]\t<--- %s\n", cmd);
}

void			log_server_response(char *cmd)
{
	printf("[CTRL]\t---> %s\n", cmd);
}
