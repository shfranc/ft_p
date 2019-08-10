#include "server.h"

uint16_t		get_random_port(void)
{
	return ((uint16_t)rand() % (USHRT_MAX + 1023) - 1023);
}

// void			extended_passive_mode(int client_sock)
// {
// 	int		data_sock;
// 	int		dtp_port;

// 	srand(time(NULL));
// 	dtp_port = get_random_port();
// 	while ((data_sock = create_server(dtp_port)) == -1)
// 		dtp_port = get_random_port();

// 	dprintf(client_sock, "PORT %d,%d\r\n", (unsigned char)dtp_port, (unsigned char)(dtp_port >> 8));
// }

int			passive_mode(int client_sock)
{
	int					data_sock;
	int					client_data_sock;
	struct sockaddr_in	data_sin;
	unsigned int		data_sin_len;
	uint16_t			dtp_port;

	srand(time(NULL));
	setbuf(stdout, NULL);
	dtp_port = get_random_port();
	printf("Try binding to %d", dtp_port);
	while ((data_sock = create_server(dtp_port)) == -1)
	{
		close(data_sock);
		dtp_port = get_random_port();
		printf("Try binding to port %d\n", dtp_port);
	}
	if (data_sock != -1)
		printf("Data channel open on port %d\n", dtp_port);

	dprintf(client_sock, "227 plop (127,0,0,1,%d,%d)\r\n", (unsigned char)dtp_port, (unsigned char)(dtp_port >> 8));

	if ((client_data_sock = accept(data_sock,
		(struct sockaddr *)&data_sin, &data_sin_len)) < 0)
		return(ret_error("accept: error"));


	return (data_sock);
}

