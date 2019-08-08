#include "server.h"

t_ex_ret	handle_clients(int server_sock)
{
	int					client_sock;
	struct sockaddr_in	client_sin;
	unsigned int		client_sin_len;
	int					pid;

	while (1)
	{
		ft_putendl("waiting for clients");
		if ((client_sock = accept(server_sock,
			(struct sockaddr *)&client_sin, &client_sin_len)) < 0)
			return(ret_error("accept: error"));
		if ((pid = fork()) < 0)
			return(ret_error("fork: error"));
		if (pid == 0)
		{
			handle_child_signals();
			// child process
			ft_putendl("client connected");
			if (get_client_commands(client_sock) == -1)
				exit(FAILURE);
			ft_putendl("client disconnected");
			exit(SUCCESS);
		}
		else
		{
			// parent process
			close(client_sock);
		}
	}
	return (SUCCESS);
}
