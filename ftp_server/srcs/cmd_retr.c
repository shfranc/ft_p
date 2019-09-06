#include "server.h"

static void				send_file(t_user *user, const void *ptr, size_t size)
{
	size_t	count;
	int		ret;

	log_info_nbr("Size", size);
	count = 0;
	while (count < size)
	{
		if ((ret = send(user->data_sock, ptr, size, 0)) == -1)
			return(send_to_user_ctrl(user, RESP_451));
		count += ret;
		log_info_nbr("Bytes sent", count);
		log_data_progress((count / size) * 100);
	}
	send_to_user_ctrl(user, RESP_226);
}

static void 			get_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf;
	void		*ptr;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || fstat(fd, &buf) < 0)
		return(send_to_user_ctrl(user, RESP_550));
	ptr = NULL;
	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return(send_to_user_ctrl(user, RESP_451));
	log_data_str("Sending", filename);
	send_file(user, ptr, buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
		return(send_to_user_ctrl(user, RESP_451));
	if (close(fd) < 0)
		return(send_to_user_ctrl(user, RESP_451));
}

void				cmd_retr(t_user *user, char **cmd)
{
	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock == -1)
		return (send_to_user_ctrl(user, RESP_426));
	else
		send_to_user_ctrl(user, RESP_125);
	log_info_str("Fetching", cmd[1]);
	get_file(user, cmd[1]);
	close_data_channel(user);
}
