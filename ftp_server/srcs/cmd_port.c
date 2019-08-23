#include "server.h"

static char			*get_addr_from_cmd(char *client_info)
{
	char 		**details;
	char		*addr;
	int			len;
	int			i;

	details = ft_strsplit(client_info, ',');
	if (ft_tablen(details) != 6)
	{
		ft_freetab(&details);
		return (NULL);
	}
	len = 3;
	i = 0;
	while (i < 4)
	{
		len += ft_strlen(details[i]);
		i++;
	}
	addr = ft_strnew(len);
	addr = ft_strcat(ft_strcpy(addr, details[0]), ".");
	addr = ft_strcat(ft_strcat(addr, details[1]), ".");
	addr = ft_strcat(ft_strcat(addr, details[2]), ".");
	addr = ft_strcat(addr, details[3]);
	ft_freetab(&details);
	log_info_str("address", addr);
	return (addr);
}

static uint16_t		get_port_from_cmd(char *client_info)
{
	char 		**details;
	uint16_t	port;

	details = ft_strsplit(client_info, ',');
	if (ft_tablen(details) != 6)
	{
		ft_freetab(&details);
		return (0);
	}
	port = (uint16_t)(ft_atoi(details[4]) << 8);
	port += (uint16_t)ft_atoi(details[5]);
	if (port < 1024 || port > USHRT_MAX)
	{
		ft_freetab(&details);
		return (0);
	}
	log_info_nbr("port", port);
	ft_freetab(&details);
	return (port);
}

static int		get_inet_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
		return (INADDR_ANY);
	else return (inet_addr(addr));
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
	client_sin.sin_addr.s_addr = get_inet_addr(addr);
	if (connect(client_sock, (const struct sockaddr *)&client_sin, sizeof(client_sin)))
		return (ret_error("connect: error"));
	return (client_sock);
}

void				cmd_port(t_user *user, char **cmd)
{
	log_info("Active mode");
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Fetching port...");
	if ((user->dtp_port = get_port_from_cmd(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Fetching addr...");
	if ((user->addr = get_addr_from_cmd(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	log_info("Connect to the data channel...");
	if ((user->data_sock = connect_to_client(user->addr, user->dtp_port)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	send_to_user_ctrl(user, RESP_200);
}
