/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:30:24 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:30:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			cmd_bin(char *cmd)
{
	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	if (ft_strcmp(cmd, "bin") != 0)
		return (ft_putendl("usage: bin"));
	send_to_server_ctrl("TYPE I");
	get_server_response();
	if (parse_response(g_client.resp) == SUCCESS)
		g_client.data_type = BIN;
}
