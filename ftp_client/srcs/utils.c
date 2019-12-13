/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:22 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:47:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

uint16_t		get_random_port(void)
{
	return ((uint16_t)(rand() % (USHRT_MAX - 1025 + 1) + 1025));
}

void			log_error(char *message)
{
	dprintf(STDERR_FILENO, "%s\t%s\n", LOG_ERROR, message);
}

int				ret_error(char *message)
{
	dprintf(STDERR_FILENO, "ftp: %s\n", message);
	return (-1);
}
