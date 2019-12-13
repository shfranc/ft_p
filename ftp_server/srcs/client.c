/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:48:04 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:48:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			send_to_user_ctrl(t_user *user, char *message)
{
	char		*formatted_msg;

	log_server_response(message);
	if (!(formatted_msg = ft_strnew(ft_strlen(message) + 2)))
		ft_exit("malloc", 1);
	formatted_msg = ft_strcat(ft_strcpy(formatted_msg, message), END_OF_MESG);
	send(user->control_sock, formatted_msg, ft_strlen(formatted_msg), 0);
	free(formatted_msg);
}

void			close_data_channel(t_user *user)
{
	close(user->data_sock);
	close(user->server_dtp_sock);
	user->data_sock = -1;
	user->server_dtp_sock = -1;
}
