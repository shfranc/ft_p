/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_epsv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:30:31 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:36:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static char		**parse_response_epsv(char *msg)
{
	char	**details;
	char	*start;
	char	*end;
	char	*tmp;

	start = ft_strchr(msg, '(');
	end = ft_strrchr(msg, ')');
	tmp = ft_strsub(msg, start - msg + 1, end - start - 1);
	details = ft_strsplit(tmp, '|');
	free(tmp);
	return (details);
}

void			cmd_epsv(void)
{
	char		**details;

	log_info("Extended passive mode");
	send_to_server_ctrl("EPSV");
	get_server_response();
	if (parse_response(g_client.resp) != RESP_SUCCESS)
		return (log_error("Failed to connect to the data channel."));
	details = parse_response_epsv(g_client.resp);
	ft_puttab(details);
	g_client.data_port = ft_atoi(details[0]);
	log_info_msg("addr", g_client.addr);
	log_info_nb("port", g_client.data_port);
	if ((g_client.data_sock = connect_to_server(g_client.addr,
		g_client.data_port)) == -1)
		return (log_error("Failed to connect to the data channel."));
	ft_freetab(&details);
}
