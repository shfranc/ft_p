/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_clients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:27:08 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:49:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		init_user(t_user *user)
{
	ft_bzero(user, sizeof(user));
	user->control_sock = -1;
	user->server_dtp_sock = -1;
	user->data_sock = -1;
	user->dtp_port = 0;
	user->data_type = ASCII;
	user->cwd = NULL;
	user->addr = NULL;
}

static void		init_root_dir_user(t_user *user)
{
	user->cwd = ft_strdup("/");
	logger(LOG_INFO, "cwd", user->cwd);
}

static int		handle_client(t_user *user)
{
	handle_child_signals();
	logger(LOG_INFO, "Client connected", NULL);
	init_root_dir_user(user);
	send_to_user_ctrl(user, RESP_220);
	get_client_commands(user);
	ft_strdel(&user->cwd);
	ft_strdel(&user->addr);
	logger(LOG_INFO, "Client disconnected", NULL);
	exit(0);
}

void			handle_clients(int server_sock)
{
	t_user				user;
	struct sockaddr_in	client_sin;
	unsigned int		client_sin_len;
	int					pid;

	logger(LOG_INFO, "Waiting for clients", NULL);
	init_user(&user);
	while (1)
	{
		if ((user.control_sock = accept(server_sock,
			(struct sockaddr *)&client_sin, &client_sin_len)) < 0)
			return (log_error("accept: error"));
		if ((pid = fork()) < 0)
			return (log_error("fork: error"));
		if (pid == 0)
			handle_client(&user);
		else
			close(user.control_sock);
	}
	return ;
}
