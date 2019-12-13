/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_channel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:31:33 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:40:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		passive_mode(void)
{
	if (g_client.family == IP_V4)
		cmd_pasv();
	else if (g_client.family == IP_V6)
		cmd_epsv();
	if (g_client.data_sock != -1)
		log_info("Data channel connected");
}

static void		active_mode(void)
{
	if (g_client.family == IP_V4)
		cmd_port();
	else if (g_client.family == IP_V6)
		cmd_eprt();
	if (g_client.data_sock != -1)
		ft_putendl("Data channel connected");
}

t_ex_ret		open_data_channel(void)
{
	if (g_client.pass == ON)
		passive_mode();
	else if (g_client.pass == OFF)
		active_mode();
	else if (g_client.pass == AUTO)
	{
		passive_mode();
		if (g_client.data_sock == -1)
			active_mode();
	}
	if (g_client.data_sock != -1)
		return (SUCCESS);
	return (FAILURE);
}
