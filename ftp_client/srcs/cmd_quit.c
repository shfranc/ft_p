#include "client.h"

void		cmd_quit(char *cmd)
{
	(void)cmd;
	send_to_server_ctrl("QUIT");
}
