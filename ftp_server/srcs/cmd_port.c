/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:19 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:37:29 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char			*get_addr_from_cmd_ipv4(char *client_info)
{
	char		**details;
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
		len += ft_strlen(details[i++]);
	addr = ft_strnew(len);
	addr = ft_strcat(ft_strcpy(addr, details[0]), ".");
	addr = ft_strcat(ft_strcat(addr, details[1]), ".");
	addr = ft_strcat(ft_strcat(addr, details[2]), ".");
	addr = ft_strcat(addr, details[3]);
	ft_freetab(&details);
	logger(LOG_INFO, "address", addr);
	return (addr);
}

static uint16_t		get_port_from_cmd_ipv4(char *client_info)
{
	char		**details;
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
	logger_nb(LOG_INFO, "port", port);
	ft_freetab(&details);
	return (port);
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
	if (connect(client_sock, (const struct sockaddr *)&client_sin,
		sizeof(client_sin)) == -1)
		return (ret_error("connect: error"));
	return (client_sock);
}

void				cmd_port(t_user *user, char **cmd)
{
	logger(LOG_INFO, "Active mode", NULL);
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "Fetching addr...", NULL);
	if ((user->addr = get_addr_from_cmd_ipv4(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "Fetching port...", NULL);
	if ((user->dtp_port = get_port_from_cmd_ipv4(cmd[1])) == 0)
		return (send_to_user_ctrl(user, RESP_501));
	logger(LOG_INFO, "Connect to the data channel...", NULL);
	if ((user->data_sock = connect_to_client(user->addr, user->dtp_port)) == -1)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_425));
	}
	send_to_user_ctrl(user, RESP_200);
}
