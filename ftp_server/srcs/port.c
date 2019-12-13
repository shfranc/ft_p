/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:53:07 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:17:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

uint16_t		get_port(char *port_str)
{
	uint32_t	port;

	if (!ft_isnumber(port_str))
	{
		dprintf(STDERR_FILENO, "Unknown port: %s\n", port_str);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port < 1024 || port > USHRT_MAX)
	{
		dprintf(STDERR_FILENO, "Port range not valid: %s\n", port_str);
		return (0);
	}
	return ((uint16_t)port);
}

uint16_t		get_random_port(void)
{
	return ((uint16_t)(rand() % (USHRT_MAX - 1025 + 1) + 1025));
}
