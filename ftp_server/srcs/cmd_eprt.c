/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_eprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:06 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:33:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int			connect_to_client_sock(int client_dtp_sock, t_user *user)
{
	struct sockaddr_in		client_sin;
	struct sockaddr_in6		client_sin6;

	if (user->family == IP_V4)
	{
		client_sin.sin_family = AF_INET;
		client_sin.sin_port = htons(user->dtp_port);
		client_sin.sin_addr.s_addr = inet_addr(user->addr);
		if (connect(client_dtp_sock, (const struct sockaddr *)&client_sin,
			sizeof(client_sin)))
			return (ret_error("connect: error"));
	}
	else if (user->family == IP_V6)
	{
		client_sin6.sin6_family = AF_INET6;
		client_sin6.sin6_port = htons(user->dtp_port);
		if (inet_pton(AF_INET6, user->addr, &client_sin6.sin6_addr) == 0)
			return (ret_error("inet_pton: error"));
		if (connect(client_dtp_sock, (const struct sockaddr *)&client_sin6,
			sizeof(client_sin6)) == -1)
			return (ret_error("connect: error"));
	}
	return (0);
}

static int			connect_to_user_dtp(t_user *user)
{
	int			client_dtp_sock;

	if (!(client_dtp_sock = create_socket(user->family)))
		return (-1);
	if (connect_to_client_sock(client_dtp_sock, user) != 0)
		return (-1);
	return (client_dtp_sock);
}

void				cmd_eprt(t_user *user, char **cmd)
{
	char		**client_infos;

	logger(LOG_INFO, "Extended active mode", NULL);
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	client_infos = ft_strsplit(cmd[1], *cmd[1]);
	logger(LOG_INFO, "Fetching family protocol...", NULL);
	if ((user->family = get_family_protocol(client_infos[0])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "protocol", (user->family == IP_V6 ? "ipv6" : "ipv4"));
	logger(LOG_INFO, "Fetching addr...", NULL);
	if (!(user->addr = ft_strdup(client_infos[1])))
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "address", user->addr);
	logger(LOG_INFO, "Fetching port...", NULL);
	if ((user->dtp_port = get_port(client_infos[2])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger_nb(LOG_INFO, "port", user->dtp_port);
	logger(LOG_INFO, "Connect to the data channel...", NULL);
	if ((user->data_sock = connect_to_user_dtp(user)) == -1)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_425));
	}
	send_to_user_ctrl(user, RESP_200);
}
