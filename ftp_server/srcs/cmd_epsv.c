#include "server.h"

static char		*prepare_epsv_message(uint16_t port)
{
	char	*message;
	char	*port_str;

	port_str = ft_itoa(port);
	message = ft_strnew(ft_strlen(RESP_229) + ft_strlen(port_str) + 2);
	message = ft_strcat(ft_strcat(ft_strcpy(message,
		RESP_229), port_str), "|)");
	free(port_str);
	return (message);
}

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
	message = prepare_epsv_message(user->dtp_port);
	send_to_user_ctrl(user, message);
	free(message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		logger(LOG_INFO, "Data connection accepted.", NULL);
	return ;
}
