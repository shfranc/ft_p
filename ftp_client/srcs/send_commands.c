#include "client.h"

static void			log_server_answer(int bytes, char *response)
{
	ft_putstr("recieved ");
	ft_putnbr(bytes);
	ft_putstr(" bytes: [");
	ft_putstr(response);
	ft_putendl("]");
}

int				send_commands_to_server(int client_sock)
{
	int					ret_read;
	int					ret_write;
	char				command[BUF_SIZE];
	char				response[BUF_SIZE];

	while (1)
	{
		ft_putstr("ftp_client > ");
		// READ INSTR stdin
		ft_bzero(&command, BUF_SIZE);
		ret_read = read(STDIN_FILENO, &command, BUF_SIZE - 1);
		if (ret_read == -1)
			return (ret_error("Failed to read from stdin"));
		command[ret_read] = '\0';

		if (ft_strcmp(command, "exit\n") == 0
			|| ft_strcmp(command, "quit\n") == 0)
		{
			printf("Exiting...\n");
			return (SUCCESS);
		}

		// WRITE to server
		ret_write = write(client_sock, &command, ret_read);
		if (ret_write == -1)
			return (ret_error("Failed to write to server"));

		// READ from server
		ft_bzero(&response, BUF_SIZE);
		ret_read = read(client_sock, &response, BUF_SIZE - 1);
		if (ret_read == -1)
			return (ret_error("Failed to read from server"));
		response[ret_read] = '\0';

		// WRITE answer
		log_server_answer(ret_read, response);
	}
	return (SUCCESS);
}
