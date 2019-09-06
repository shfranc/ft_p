#include "server.h"

void			log_error(char *message)
{
	dprintf(STDERR_FILENO, "%s\t%s\n", LOG_ERROR, message);
}

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

void			log_data(char *message)
{
	printf("%s\t%s\n", LOG_DATA, message);
}

void			log_data_str(char *desc, char *message)
{
	printf("%s\t%s: %s\n", LOG_DATA, desc, message);
}

void			log_data_nbr(char *desc, int nb)
{
	printf("%s\t%s: %d\n", LOG_DATA, desc, nb);
}

void			log_data_progress(int progress)
{
	printf("%s\tProgress... %d%%\n", LOG_DATA, progress);
}
