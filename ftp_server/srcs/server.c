/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:27:20 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:19:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

	if (g_server.family == IP_V4)
	{
		server_sin.sin_family = AF_INET;
		server_sin.sin_port = htons(port);
		server_sin.sin_addr.s_addr = INADDR_ANY;
		if (bind(server_sock, (const struct sockaddr *)&server_sin,
			sizeof(server_sin)) != 0)
			return (ret_error("bind: error"));
	}
	else if (g_server.family == IP_V6)
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

int				create_server(uint16_t port)
{
	int						server_sock;

	if (!(server_sock = create_socket(g_server.family)))
		return (-1);
	if (bind_server(server_sock, port) != 0)
		return (-1);
	listen(server_sock, NB_CONNECT);
	return (server_sock);
}

int				create_dtp_server(t_user *user)
{
	int						i;

	if (!(user->server_dtp_sock = create_socket(g_server.family)))
		return (-1);
	i = 0;
	while (i < 100)
	{
		user->dtp_port = get_random_port();
		logger_nb(LOG_INFO, "Trying to bind a random port", user->dtp_port);
		if (bind_server(user->server_dtp_sock, user->dtp_port) == 0)
		{
			logger(LOG_INFO, "Port binded, server DTP created", NULL);
			listen(user->server_dtp_sock, NB_CONNECT);
			return (0);
		}
		i++;
	}
	return (ret_error("Maximum tries to find a port reach"));
}

int				close_server(void)
{
	printf("Exiting...\n");
	if (g_server.server_sock == -1
		|| close(g_server.server_sock) == -1)
		return (FAILURE);
	return (SUCCESS);
}
