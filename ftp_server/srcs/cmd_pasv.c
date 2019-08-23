#include "server.h"

static uint16_t		get_random_port(void)
{
	srand(time(NULL));
	return ((uint16_t)rand() % (USHRT_MAX + 1023) - 1023);
}

static int				create_DTP_server(t_user *user)
{
	struct protoent			*proto;
	struct sockaddr_in		server_sin;
	int						i;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(user->server_dtp_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	server_sin.sin_family = AF_INET;
	server_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	i = 0;
	while (i < 100)
	{
		log_info("Trying to bind a random port...");
		user->dtp_port = get_random_port();
		server_sin.sin_port = htons(user->dtp_port);
		if (bind(user->server_dtp_sock, (const struct sockaddr *)&server_sin, sizeof(server_sin)) == 0)
		{
			log_info("Port binded, server DTP created");
			listen(user->server_dtp_sock, NB_CONNECT);
			return (0);
		}
		i++;
	}
	return (ret_error("Maximum tries to find a port reach"));
}

void		cmd_pasv(t_user *user, char **cmd)
{
	int					ret;
	char				*message;
	struct sockaddr_in	data_sin;
	unsigned int		data_sin_len;

	(void)cmd;
	log_info("Passive mode");
	if ((ret = create_DTP_server(user)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	message = NULL;
	asprintf(&message, "227 Data chanel open (127,0,0,1,%d,%d)", (unsigned char)(user->dtp_port >> 8), (unsigned char)user->dtp_port);
	send_to_user_ctrl(user, message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		log_info("Data connection accepted.");
	return ;
}
