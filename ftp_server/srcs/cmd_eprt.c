#include "server.h"

static uint8_t		get_family_protocol(char *str_family)
{
	uint8_t family;

	family = ft_atoi(str_family);
	if (family == 1)
		return (IP_V4);
	if (family == 2)
		return (IP_V6);
	return (0);
}

static int			connect_to_client_sock(uint8_t family, int client_sock, char *addr, uint16_t port)
{
	struct sockaddr_in		client_sin;
	struct sockaddr_in6		client_sin6;

	if (family == IP_V4)
	{
		client_sin.sin_family = AF_INET;
		client_sin.sin_port = htons(port);
		client_sin.sin_addr.s_addr = inet_addr(addr);
		if (connect(client_sock, (const struct sockaddr *)&client_sin,
			sizeof(client_sin)))
			return (ret_error("connect: error"));
	}
	else if (family == IP_V6)
	{
		client_sin6.sin6_family = AF_INET6;
		client_sin6.sin6_port = htons(port);
		inet_pton(AF_INET6, addr, &client_sin6.sin6_addr);
		if (connect(client_sock, (const struct sockaddr *)&client_sin6,
			sizeof(client_sin6)))
			return (ret_error("connect: error"));
	}
	return (0);
}


static int			connect_to_client(uint8_t family, char *addr, uint16_t port)
{
	int						client_sock;
	struct protoent			*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(client_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	if (connect_to_client_sock(family, client_sock, addr, port) != 0)
		return (-1);
	return (client_sock);
}

void				cmd_eprt(t_user *user, char **cmd)
{
	char		**client_infos;
	uint8_t		family;

	logger(LOG_INFO, "Extended active mode", NULL);
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	client_infos = ft_strsplit(cmd[1], *cmd[1]);
	logger(LOG_INFO, "Fetching family protocol...", NULL);
	if ((family = get_family_protocol(client_infos[0])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "protocol", (family == IP_V6 ? "ipv6" : "ipv4"));
	logger(LOG_INFO, "Fetching addr...", NULL);
	if (!(user->addr = ft_strdup(client_infos[1])))
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "address", user->addr);
	logger(LOG_INFO, "Fetching port...", NULL);
	if ((user->dtp_port = get_port(client_infos[2])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger_nb(LOG_INFO, "port", user->dtp_port);
	logger(LOG_INFO, "Connect to the data channel...", NULL);
	if ((user->data_sock = connect_to_client(family, user->addr, user->dtp_port)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	send_to_user_ctrl(user, RESP_200);
}
