#include "client.h"

void		read_data_bin()
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	total = 0;
	while ((ret = read(g_client.data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		total += ret;
		write(STDOUT_FILENO, buf, ret);
	}
	log_info_nb("Total bytes", total);
	if (ret < 0)
		return(log_error("Error reading data from data channel"));
	return ;
}
