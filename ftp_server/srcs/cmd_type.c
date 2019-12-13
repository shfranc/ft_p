/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:30 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:33:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_type(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) > 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (ft_strcmp(cmd[1], TYPE_ASCII) == 0)
		user->data_type = ASCII;
	else if (ft_strcmp(cmd[1], TYPE_BIN) == 0)
		user->data_type = BIN;
	else
		send_to_user_ctrl(user, RESP_501);
	logger(LOG_INFO, "New type set", user->data_type == BIN ? "BIN" : "ASCII");
	send_to_user_ctrl(user, RESP_200_1);
}
