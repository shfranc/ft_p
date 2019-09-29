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
	else if (g_client.pass == AUTO)
	{
		if (connect_data_channel() == FALSE)
			return (create_data_channel);
	}
	else if (g_client.pass == OFF)
		return (create_data_channel());
}
