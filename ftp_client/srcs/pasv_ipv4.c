#include "client.h"

static char		*get_addr(char **details)
{
	char		*addr;
	int			len;
	int			i;

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
	return (addr);
}

static uint16_t	get_port(char **details)
{
	return ((uint16_t)(ft_atoi(details[4]) << 8)
		+ ft_atoi(details[5]));
}

static char		**parse_response_pasv(char *msg)
{
	char	**details;
	char	*start;
	char	*end;
	char	*tmp;

	start = ft_strchr(msg, '(');
	end = ft_strrchr(msg, ')');
	tmp = ft_strsub(msg, start - msg + 1, end - start);
	details = ft_strsplit(tmp, ',');
	free(tmp);
	return (details);
}

static int		connect_to_DTP_server_ipv4(char *addr, int port)
{
	int						server_sock;
	struct protoent			*proto;
	struct sockaddr_in		server_sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(server_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	server_sin.sin_family = AF_INET;
	server_sin.sin_port = htons(port);
	server_sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(server_sock, (const struct sockaddr *)&server_sin, sizeof(server_sin)) == -1)
		return (ret_error("connect: error"));
	return (server_sock);
}

// 227 Entering passive mode (0,0,0,0,39,130)

void			connect_data_channel_ipv4()
{
	char		**details;
	char		*addr;
	uint16_t	port;

	send_to_server_ctrl("PASV");
	get_server_response();
	if (parse_response(g_client.resp) != RESP_SUCCESS)
	{
		log_error("Failed to connect to the data channel.");
		return ;
	}
	details = parse_response_pasv(g_client.resp);
	if (ft_tablen(details) != 6)
		return (log_error("PASV answer: Wrong format"));
	addr = get_addr(details);
	port = get_port(details);
	log_info_msg("addr", addr);
	log_info_nb("port", port);
	g_client.data_sock = connect_to_DTP_server_ipv4(addr, port);
	free(addr);
}

