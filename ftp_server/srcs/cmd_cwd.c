#include "server.h"

void		cmd_cwd(t_user *user, char **cmd)
{
	(void)user;
	(void)cmd;
	send_to_user_ctrl(user, RESP_250);
}
