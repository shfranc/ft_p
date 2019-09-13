#include "server.h"

void			logger(char *lvl, char *info1, char *info2)
{
	if (is_option_activated('d') == FALSE)
		return ;
	if (info2)
		printf("%s\t%s: %s\n", lvl, info1, info2);
	else
		printf("%s\t%s\n", lvl, info1);
}

void			logger_nb(char *lvl, char *info1, int nb)
{
	if (is_option_activated('d') == FALSE)
		return ;
		printf("%s\t%s: %d\n", lvl, info1, nb);
}

void			log_error(char *message)
{
	dprintf(STDERR_FILENO, "%s\t%s\n", LOG_ERROR, message);
}

void			log_client_command(char *cmd)
{
	if (is_option_activated('v') == TRUE || is_option_activated('d') == TRUE)
		printf("%s\t<--- %s\n", LOG_CTRL, cmd);
}

void			log_server_response(char *cmd)
{
	if (is_option_activated('v') == TRUE || is_option_activated('d') == TRUE)
		printf("%s\t---> %s\n", LOG_CTRL, cmd);
}
