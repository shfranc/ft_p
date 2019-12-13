/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:31:23 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:39:40 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static char		*prepare_port_message(uint16_t port)
{
	const char	*start = "PORT 0,0,0,0,";
	char		*message;
	char		*port_part1;
	char		*port_part2;

	port_part1 = ft_itoa((unsigned char)(port >> 8));
	port_part2 = ft_itoa((unsigned char)port);
	message = ft_strnew(ft_strlen(start) \
		+ ft_strlen(port_part1) \
		+ ft_strlen(port_part2) + 1);
	message = ft_strcpy(message, start);
	message = ft_strcat(message, port_part1);
	message = ft_strcat(message, ",");
	message = ft_strcat(message, port_part2);
	free(port_part1);
	free(port_part2);
	return (message);
}

void			cmd_port(void)
{
	char				*message;
	struct sockaddr_in	data_sin;
	socklen_t			data_sin_len;

	log_info("Active mode");
	if (create_dtp_server() == -1)
		return (log_error("Fail to create data channel"));
	message = prepare_port_message(g_client.data_port);
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
