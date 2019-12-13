/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:31:38 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:41:10 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			log_info(char *message)
{
	if (is_option_activated('d'))
		printf("%s\t%s\n", LOG_INFO, message);
}

void			log_info_msg(char *desc, char *message)
{
	if (is_option_activated('d'))
		printf("%s\t%s: %s\n", LOG_INFO, desc, message);
}

void			log_info_nb(char *desc, int nb)
{
	if (is_option_activated('d'))
		printf("%s\t%s: %d\n", LOG_INFO, desc, nb);
}

void			log_client_command(char *cmd)
{
	if (is_option_activated('v') || is_option_activated('d'))
		printf("%s\t---> %s\n", LOG_CTRL, cmd);
	else
		printf("---> %s\n", cmd);
}

void			log_server_response(char *cmd)
{
	if (is_option_activated('v') || is_option_activated('d'))
		printf("%s\t<--- %s\n", LOG_CTRL, cmd);
	else
		printf("<--- %s\n", cmd);
}
