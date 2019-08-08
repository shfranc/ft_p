#include "client.h"

int		ret_error(char *message)
{
	dprintf(STDERR_FILENO, "./client: %s\n", message);
	return (-1);
}
