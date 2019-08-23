#include "server.h"

void				cmd_retr(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	log_data_str("Sending", cmd[1]);
	send_to_user_ctrl(user, RESP_226);
}
