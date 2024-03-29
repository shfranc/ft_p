/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:27:23 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:27:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handle_sigint(int sig)
{
	(void)sig;
	close_server();
	exit(FAILURE);
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}
