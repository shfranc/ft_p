#include "server.h"

void		cmd_pasv(t_user *user, char **cmd)
{
	int					ret;
	char				*message;
	struct sockaddr_in	data_sin;
	unsigned int		data_sin_len;

	if (ft_tablen(cmd) > 1)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	logger(LOG_INFO, "Passive mode", NULL);
	if ((ret = create_DTP_server(user)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	message = NULL;
	asprintf(&message, "227 Entering passive mode (0,0,0,0,%d,%d)", (unsigned char)(user->dtp_port >> 8), (unsigned char)user->dtp_port);
	send_to_user_ctrl(user, message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		logger(LOG_INFO, "Data connection accepted.", NULL);
	return ;
}
