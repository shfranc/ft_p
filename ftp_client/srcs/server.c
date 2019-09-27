#include "client.h"

void				get_server_response()
{
	int					ret;
	char				buf[BUF_SIZE];

	g_client.resp ? free(g_client.resp) : 0;
	ret = read(g_client.ctrl_sock, &buf, BUF_SIZE - 1);
	if (buf[ret - 2] == '\r')
		buf[ret - 2] = '\0';
	else if (buf[ret - 1] == '\n')
		buf[ret - 1] = '\0';
	else
		buf[ret] = '\0';
	if (ret == -1)
		return (log_error("read: Failed to read from client"));
	g_client.resp = ft_strdup(buf);
	return (log_server_response(buf));
}
