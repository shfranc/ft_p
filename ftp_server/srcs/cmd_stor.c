/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:27 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:41:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		put_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf_stat;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0 || fstat(fd, &buf_stat) < 0)
	{
		return (send_to_user_ctrl(user, RESP_451));
	}
	logger(LOG_DATA, "Receiving", filename);
	if (user->data_type == ASCII)
		return (read_data_ascii(user, fd));
	else if (user->data_type == BIN)
		return (read_data_bin(user, fd));
}

void		cmd_stor(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock == -1)
		return (send_to_user_ctrl(user, RESP_426));
	else
		send_to_user_ctrl(user, RESP_125);
	logger(LOG_INFO, "Preparing to receive", cmd[1]);
	put_file(user, cmd[1]);
	close_data_channel(user);
}
