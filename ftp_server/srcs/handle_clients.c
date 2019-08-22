#include "server.h"

void			send_to_user_ctrl(t_user *user, char *message)
{
	log_server_response(message);
	send(user->control_sock, message, ft_strlen(message), 0);
	send(user->control_sock, END_OF_MESG, ft_strlen(END_OF_MESG), 0);
}

void			close_data_channel(t_user *user)
{
	close(user->data_sock);
	close(user->server_dtp_sock);
	user->data_sock = -1;
	user->server_dtp_sock = -1;
}

static void		init_user(t_user *user)
{
	user->control_sock = -1;
	user->server_dtp_sock = -1;
	user->data_sock = -1;
	user->dtp_port = 0;
}

t_ex_ret		handle_clients(int server_sock)
{
	t_user				user;
	struct sockaddr_in	client_sin;
	unsigned int		client_sin_len;
	int					pid;

	init_user(&user);
	while (1)
	{
		log_info("waiting for clients");
		if ((user.control_sock = accept(server_sock,
			(struct sockaddr *)&client_sin, &client_sin_len)) < 0)
			return(ret_error("accept: error"));
		if ((pid = fork()) < 0)
			return(ret_error("fork: error"));
		if (pid == 0)
		{
			handle_child_signals();
			log_info("client connected");
			send_to_user_ctrl(&user, RESP_220);
			if (get_client_commands(&user) == -1)
				exit(FAILURE);
			log_info("client disconnected");
			exit(SUCCESS);
		}
		else
		{
			close(user.control_sock);
		}
	}
	return (SUCCESS);
}
