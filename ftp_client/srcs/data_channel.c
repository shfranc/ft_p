#include "client.h"

static void		passive_mode() // PASV - EPSV
{
	if (g_client.family == IP_V4)
	{
		cmd_pasv();
		log_info("data channel connected");
	}
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
	if (g_client.data_sock != -1)
		return (SUCCESS);
	return (FAILURE);
}
