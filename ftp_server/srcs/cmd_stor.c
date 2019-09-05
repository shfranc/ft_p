#include "server.h"

void				cmd_stor(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock == -1)
		return (send_to_user_ctrl(user, RESP_426));
	else
		send_to_user_ctrl(user, RESP_125);
	log_info_str("Recieving", cmd[1]);
	send_to_user_ctrl(user, RESP_226);
	close_data_channel(user);
}
