#include "server.h"

int				ret_error(char *message)
{
	dprintf(STDERR_FILENO, "./server: %s\n", message);
	return (-1);
}

t_ex_ret		ret_failure(char *message)
{
	dprintf(STDERR_FILENO, "./server: %s\n", message);
	return (FAILURE);
}
