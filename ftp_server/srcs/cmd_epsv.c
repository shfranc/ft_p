#include "server.h"

static uint16_t		get_random_port(void)
{
	srand(time(NULL));
	return ((uint16_t)rand() % (USHRT_MAX + 1023) - 1023);
}

static int				create_DTP_server(t_user *user)
{
	int						i;

	if (!(user->server_dtp_sock = create_socket(g_server.family)))
		return (-1);
	i = 0;
	while (i < 100)
	{
		user->dtp_port = get_random_port();
		log_info_nbr("Trying to bind a random port", user->dtp_port);
		if (bind_server(user->server_dtp_sock, user->dtp_port) == 0)
		{
			log_info("Port binded, server DTP created");
			listen(user->server_dtp_sock, NB_CONNECT);
			return (0);
		}
		i++;
	}
	return (ret_error("Maximum tries to find a port reach"));
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
	log_info("Extended passive mode");
	if ((ret = create_DTP_server(user)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	message = NULL;
	asprintf(&message, "229 Entering extended passive mode (|||%d|)", user->dtp_port);
	send_to_user_ctrl(user, message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		log_info("Data connection accepted.");
	return ;
}
