#include "server.h"

void	cmd_type(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) > 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (ft_strcmp(cmd[1], TYPE_ASCII) == 0)
		user->data_type = ASCII;
	else if (ft_strcmp(cmd[1], TYPE_BIN) == 0)
		user->data_type = BIN;
	else
		send_to_user_ctrl(user, RESP_501);
	logger(LOG_INFO, "New type set", user->data_type == ASCII ? "ASCII" : "BIN");
	send_to_user_ctrl(user, RESP_200_1);
}
