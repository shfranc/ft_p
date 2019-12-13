/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ascii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:30:21 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:30:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			cmd_ascii(char *cmd)
{
	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	if (ft_strcmp(cmd, "ascii") != 0)
		return (ft_putendl("usage: ascii"));
	send_to_server_ctrl("TYPE A");
	get_server_response();
	if (parse_response(g_client.resp) == SUCCESS)
		g_client.data_type = ASCII;
}
