/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:31:25 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:40:15 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void				send_file(char *filename)
{
	int			fd;
	struct stat buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || fstat(fd, &buf) < 0)
		return (log_error("Failed to open file"));
	if (g_client.data_type == ASCII)
		send_data_ascii(fd, buf.st_size);
	else if (g_client.data_type == BIN)
		send_data_bin(fd, buf.st_size);
	close_data_sock();
	get_server_response();
	parse_response(g_client.resp);
}

void					cmd_put(char *cmd)
{
	char	**params;
	char	*message;

	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	params = ft_strsplit(cmd, ' ');
	if (ft_tablen(params) != 3)
	{
		ft_freetab(&params);
		return (ft_putendl("usage: put local-file remote-file"));
	}
	if (open_data_channel() == FAILURE)
	{
		ft_freetab(&params);
		return (log_error("put command aborted"));
	}
	message = ft_strjoin("STOR ", params[2]);
	send_to_server_ctrl(message);
	get_server_response();
	send_file(params[1]);
	free(message);
	ft_freetab(&params);
	close_server_dtp_sock();
}
