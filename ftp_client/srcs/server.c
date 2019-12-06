#include "client.h"

uint16_t		get_random_port(void)
{
	srand(time(NULL));
	return ((uint16_t)rand() % (USHRT_MAX + 1023) - 1023);
}

int				create_socket(int family)
{
	int						server_sock;
	struct protoent			*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (family == IP_V4)
	{
		if (!(server_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
			return (ret_error("socket inet: error"));
		return (server_sock);
	}
	else if (family == IP_V6)
	{
		if (!(server_sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)))
			return (ret_error("socket inet6: error"));
		return (server_sock);
	}
	return (0);
}

int				bind_server(int server_sock, uint16_t port)
{
	struct sockaddr_in		server_sin;
	struct sockaddr_in6		server_sin6;

	if (g_client.family == IP_V4)
	{
		server_sin.sin_family = AF_INET;
		server_sin.sin_port = htons(port);
		server_sin.sin_addr.s_addr = INADDR_ANY;
		if (bind(server_sock, (const struct sockaddr *)&server_sin,
			sizeof(server_sin)) != 0)
			return (ret_error("bind: error"));
	}
	else if (g_client.family == IP_V6)
	{
		server_sin6.sin6_family = AF_INET6;
		server_sin6.sin6_port = htons(port);
		server_sin6.sin6_addr = in6addr_any;
		if (bind(server_sock, (const struct sockaddr *)&server_sin6,
			sizeof(server_sin6)) != 0)
			return (ret_error("bind: error"));
	}
	return (0);
}

void				send_to_server_ctrl(char *message)
{
	char		*formatted_msg;

	log_client_command(message);
	if (!(formatted_msg = ft_strnew(ft_strlen(message) + 2)))
		ft_exit("malloc", 1);
	formatted_msg = ft_strcat(ft_strcpy(formatted_msg, message), END_OF_MESG);
	send(g_client.ctrl_sock, formatted_msg, ft_strlen(formatted_msg), 0);
	free(formatted_msg);
}

void				get_server_response()
{
	int					ret;
	char				buf[BUF_SIZE];

	g_client.resp ? free(g_client.resp) : 0;
	ret = read(g_client.ctrl_sock, &buf, BUF_SIZE - 1);
	if (ret == -1)
		return (log_error("read: Failed to read from client"));
	if (buf[ret - 2] == '\r')
		buf[ret - 2] = '\0';
	else if (buf[ret - 1] == '\n')
		buf[ret - 1] = '\0';
	else
		buf[ret] = '\0';
	g_client.resp = ft_strdup(buf);
	return (log_server_response(g_client.resp));
}
