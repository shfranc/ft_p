#include "client.h"

static char		*format_addr(char **details)
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

static char		*parse_response_addr_ipv4(char *msg)
{
	char	**details;
	char	*start;
	char	*end;
	char	*tmp;
	char	*addr;

	start = ft_strchr(msg, '(');
	end = ft_strrchr(msg, ')');
	tmp = ft_strsub(msg, start - msg + 1, end - start);
	details = ft_strsplit(tmp, ',');
	addr = format_addr(details);
	printf("%s\n", addr);
	free(tmp);
	ft_freetab(&details);
	return (addr);
}

static int		parse_response_port_ipv4(char *msg)
{	(void)msg;

	return (65000);
}

static int		connect_to_DTP_server(char *addr, int port)
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
	char	*addr;
	int		port;

	send_to_server_ctrl("PASV");
	get_server_response();
	if (parse_response(g_client.resp) != RESP_SUCCESS)
	{
		log_error("Failed to connect to the data channel.");
		return ;
	}
	addr = parse_response_addr_ipv4(g_client.resp);
	port = parse_response_port_ipv4(g_client.resp);
	g_client.data_sock = connect_to_DTP_server(addr, port);
}

