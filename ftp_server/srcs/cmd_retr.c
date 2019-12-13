/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:25 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:44:56 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_bool			check_file_path(t_user *user, char *filename)
{
	char		*virtual_path;

	logger(LOG_INFO, "Trying to fetch", filename);
	virtual_path = convert_path_real_to_virtual(filename);
	if (is_valid_path(virtual_path) == FALSE)
	{
		free(virtual_path);
		logger(LOG_INFO, "Invalid path, no get performed.", NULL);
		send_to_user_ctrl(user, RESP_550_1);
		return (FALSE);
	}
	free(virtual_path);
	return (TRUE);
}

static void				get_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf;

	if (check_file_path(user, filename) == FALSE)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || fstat(fd, &buf) < 0)
		return (send_to_user_ctrl(user, RESP_550));
	if (user->data_type == ASCII)
		return (send_data_ascii(user, fd, buf.st_size));
	else if (user->data_type == BIN)
		return (send_data_bin(user, fd, buf.st_size));
}

void					cmd_retr(t_user *user, char **cmd)
{
	char		*abs_virtual_path;
	char		*real_path;

	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock == -1)
		return (send_to_user_ctrl(user, RESP_426));
	else
		send_to_user_ctrl(user, RESP_125);
	logger(LOG_INFO, "Fetching", cmd[1]);
	abs_virtual_path = get_virtual_absolute_path(user, cmd[1]);
	real_path = convert_path_virtual_to_real(abs_virtual_path);
	get_file(user, real_path);
	free(abs_virtual_path);
	free(real_path);
	close_data_channel(user);
}
