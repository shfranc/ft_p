#include "server.h"

static void			log_client_command(int bytes, char *cmd)
{
	ft_putstr("recieved ");
	ft_putnbr(bytes);
	ft_putstr(" bytes: [");
	ft_putstr(cmd);
	ft_putendl("]");
}

int					get_client_commands(int client_sock)
{
	int					ret;
	char				buf[BUF_SIZE];

	ft_putendl("waiting for client command");
	while ((ret = read(client_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		ft_putendl("waiting for client command");
		buf[ret] = '\0';
		log_client_command(ret, buf);
		if (write(client_sock, "OK\n", 3) == -1)
			return (ret_error("write: Failed to write to client"));
	}
	if (ret == -1)
	{
		close(client_sock);
		return (ret_error("read: Failed to read from client"));
	}
	close(client_sock);
	return (SUCCESS);
}
