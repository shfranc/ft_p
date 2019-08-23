#include "server.h"

void	cmd_type(t_user *user, char **cmd)
{
	(void)cmd;
	send_to_user_ctrl(user, RESP_200_1);
}
