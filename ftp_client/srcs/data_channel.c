#include "client.h"

// static void		connect_data_channel_ipv6()
// {
// 	send_to_server_ctrl("EPSV");
// }


static void		passive_mode() // PASV - EPSV
{
	if (g_client.family == IP_V4)
		connect_data_channel_ipv4();
	else if (g_client.family == IP_V6)
		;
}

static void		active_mode() // PORT - EPRT
{

}

t_ex_ret		open_data_channel()
{
	if (g_client.pass == ON)
		passive_mode();
	else if (g_client.pass == OFF)
		active_mode();
	else if (g_client.pass == AUTO)
	{
		passive_mode();
		if (g_client.data_sock == -1)
			active_mode();
	}
	get_server_response();
	if (parse_response(g_client.resp) == RESP_SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
