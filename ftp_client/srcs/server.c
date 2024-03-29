/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:17 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/20 20:51:29 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

int				create_dtp_server(void)
{
	int						i;

	if (!(g_client.server_dtp_sock = create_socket(g_client.family)))
		return (-1);
	i = 0;
	while (i < 100)
	{
		g_client.data_port = get_random_port();
		log_info_nb("Trying to bind a random port", g_client.data_port);
		if (bind_server(g_client.server_dtp_sock, g_client.data_port) == 0)
		{
			log_info("Port binded, server DTP created");
			listen(g_client.server_dtp_sock, 1);
			return (0);
		}
		i++;
	}
	return (ret_error("Maximum tries to find a port reach"));
}

void			send_to_server_ctrl(char *message)
{
	char		*formatted_msg;

	log_client_command(message);
	if (!(formatted_msg = ft_strnew(ft_strlen(message) + 2)))
		ft_exit("malloc", 1);
	formatted_msg = ft_strcat(ft_strcpy(formatted_msg, message), END_OF_MESG);
	send(g_client.ctrl_sock, formatted_msg, ft_strlen(formatted_msg), 0);
	free(formatted_msg);
}

void			get_server_response(void)
{
	int					ret;
	int					len;
	static char			buf[BUF_SIZE];
	char				*stop;

	ret = 0;
	g_client.resp ? free(g_client.resp) : 0;
	if (buf[0] == '\0')
		ret = recv(g_client.ctrl_sock, &buf, BUF_SIZE - 1, 0);
	stop = ft_strstr(buf, END_OF_MESG);
	if (ret == -1 || !stop)
		return (log_error("read: Failed to read from client"));
	g_client.resp = ft_strsub(buf, 0, stop - buf);
	if (*(stop + ft_strlen(END_OF_MESG)))
	{
		len = ft_strlen(stop) - ft_strlen(END_OF_MESG);
		ft_memcpy(buf, stop + ft_strlen(END_OF_MESG), len);
		ft_bzero(buf + len, BUF_SIZE - len);
	}
	else
		ft_bzero(buf, BUF_SIZE);
	log_server_response(g_client.resp);
	return ;
}
