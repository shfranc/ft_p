#include "client.h"

void				send_to_server_ctrl(char *message)
{
	char		*formatted_msg;

	log_client_command(message);
	if (!(formatted_msg = ft_strnew(ft_strlen(message) + 2)))
		ft_exit("malloc", 1);
	formatted_msg = ft_strcat(ft_strcpy(formatted_msg, message), END_OF_MESG);
	send(g_client.ctrl_sock, formatted_msg, ft_strlen(formatted_msg), 0);
	free(formatted_msg);
}

void				get_server_response()
{
	int					ret;
	char				buf[BUF_SIZE];

	g_client.resp ? free(g_client.resp) : 0;
	ret = read(g_client.ctrl_sock, &buf, BUF_SIZE - 1);
	printf("%d\n", ret);
	if (ret == -1)
		return (log_error("read: Failed to read from client"));
	if (buf[ret - 2] == '\r')
		buf[ret - 2] = '\0';
	else if (buf[ret - 1] == '\n')
		buf[ret - 1] = '\0';
	else
		buf[ret] = '\0';
	ft_putendl(buf);
	g_client.resp = ft_strdup(buf);
	return (log_server_response(g_client.resp));
}
