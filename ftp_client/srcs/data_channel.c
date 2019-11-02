#include "client.h"

static void		connect_data_channel()
{
	

}

static void		create_data_channel()
{

}

void		open_data_channel()
{
	if (g_client.pass == ON)
		return (connect_data_channel());
	if (g_client.pass == OFF)
		return (create_data_channel());
	else if (g_client.pass == AUTO)
	{
		connect_data_channel();
		if (g_client.data_sock == -1)
			return (create_data_channel());
	}
}
