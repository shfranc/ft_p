#include "server.h"

static char			*get_addr_from_cmd_ipv6(char *client_info)
{
	(void)client_info;
	return (NULL);
}

static uint16_t		get_port_from_cmd_ipv6(char *client_info)
{
	(void)client_info;
	return (0);
}

static int			connect_to_client(char *addr, int port)
{
	int						client_sock;
	struct protoent			*proto;
	struct sockaddr_in		client_sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(client_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	client_sin.sin_family = AF_INET;
	client_sin.sin_port = htons(port);
	client_sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(client_sock, (const struct sockaddr *)&client_sin, sizeof(client_sin)))
		return (ret_error("connect: error"));
	return (client_sock);
}

void				cmd_eprt(t_user *user, char **cmd)
{
	log_info("Extended active mode");
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Fetching port...");
	if ((user->dtp_port = get_port_from_cmd_ipv6(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Fetching addr...");
	if ((user->addr = get_addr_from_cmd_ipv6(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Connect to the data channel...");
	if ((user->data_sock = connect_to_client(user->addr, user->dtp_port)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	send_to_user_ctrl(user, RESP_200);
}
