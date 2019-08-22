#include "server.h"

void			log_info(char *message)
{
	printf("[INFO]\t%s\n", message);
}

void			log_client_command(char *cmd)
{
	printf("[CTRL]\t<--- %s\n", cmd);
}

