#include "server.h"

uint16_t		get_random_port(void)
{
	return ((uint16_t)rand() % (USHRT_MAX + 1023) - 1023);
}

void		cmd_pasv(t_user *user)
{
	(void)user;
}
