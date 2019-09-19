#include "server.h"

void		cmd_epsv(t_user *user, char **cmd)
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
	logger(LOG_INFO, "Extended passive mode", NULL);
	if ((ret = create_DTP_server(user)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	message = NULL;
	asprintf(&message, "229 Entering extended passive mode (|||%d|)", user->dtp_port);
	send_to_user_ctrl(user, message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		logger(LOG_INFO, "Data connection accepted.", NULL);
	return ;
}
