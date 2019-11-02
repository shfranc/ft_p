#include "client.h"

t_reply			parse_response(char *response)
{
	if (!*response)
		return (RESP_ERROR);
	if (*response == '1' || *response == '2' || *response == '3')
		return (RESP_SUCCESS);
	else if (*response == '4' || *response == '5')
		return (RESP_FAILURE);
	else
		return (RESP_ERROR);
}
