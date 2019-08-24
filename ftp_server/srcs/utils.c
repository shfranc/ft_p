#include "server.h"

int				ret_error(char *message)
{
	log_error(message);
	return (-1);
}

t_ex_ret		ret_failure(char *message)
{
	log_error(message);
	return (FAILURE);
}
