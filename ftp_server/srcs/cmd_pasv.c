/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:16 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:19:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char		*prepare_pasv_message(uint16_t port)
{
	char	*port_part1;
	char	*port_part2;
	char	*message;

	port_part1 = ft_itoa((unsigned char)(port >> 8));
	port_part2 = ft_itoa((unsigned char)port);
	message = ft_strnew(ft_strlen(RESP_227) + ft_strlen(port_part1)
		+ ft_strlen(port_part2) + 2);
	message = ft_strcat(ft_strcpy(message, RESP_227), port_part1);
	message = ft_strcat(ft_strcat(ft_strcat(message, ","), port_part2), ")");
	free(port_part1);
	free(port_part2);
	return (message);
}

void			cmd_pasv(t_user *user, char **cmd)
{
	int					ret;
	char				*message;
	struct sockaddr_in	data_sin;
	unsigned int		data_sin_len;

	if (ft_tablen(cmd) > 1)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	logger(LOG_INFO, "Passive mode", NULL);
	if ((ret = create_dtp_server(user)) == -1)
		return (send_to_user_ctrl(user, RESP_425));
	message = prepare_pasv_message(user->dtp_port);
	send_to_user_ctrl(user, message);
	free(message);
	if ((user->data_sock = accept(user->server_dtp_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		send_to_user_ctrl(user, RESP_425);
	else
		logger(LOG_INFO, "Data connection accepted.", NULL);
	return ;
}
