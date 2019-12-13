/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:19 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:32:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nExiting...\n");
	close(g_client.ctrl_sock);
	exit(FAILURE);
}
