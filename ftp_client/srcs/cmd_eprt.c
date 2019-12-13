/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_eprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:30:29 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:37:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static char		*get_family_protocol(int family)
{
	return (family == IP_V4 ? ft_strdup("1") : ft_strdup("2"));
}

static char		*prepare_eprt_message(void)
{
	const char	*start = "EPRT |";
	char		*family;
	char		*port;
	char		*message;

	family = get_family_protocol(g_client.family);
	port = ft_itoa(g_client.data_port);
	message = ft_strnew(ft_strlen(start) \
		+ ft_strlen(g_client.addr) \
		+ ft_strlen(port) + 4);
	message = ft_strcpy(message, start);
	message = ft_strcat(message, family);
	message = ft_strcat(message, "|");
	message = ft_strcat(message, g_client.addr);
	message = ft_strcat(message, "|");
	message = ft_strcat(message, port);
	message = ft_strcat(message, "|");
	free(family);
	free(port);
	return (message);
}

void			cmd_eprt(void)
{
	char				*message;
	struct sockaddr_in	data_sin;
	socklen_t			data_sin_len;

	data_sin_len = 0;
	log_info("Extended active mode");
	if (create_dtp_server() == -1)
		return (log_error("Fail to create data channel"));
	message = prepare_eprt_message();
	send_to_server_ctrl(message);
	get_server_response();
	if (parse_response(g_client.resp) != RESP_SUCCESS)
	{
		log_error("Server failed to connect to the data channel.");
		close_server_dtp_sock();
	}
	else if ((g_client.data_sock = accept(g_client.server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
	{
		log_error("Server failed to connect to the data channel.");
		close_server_dtp_sock();
	}
	free(message);
}
