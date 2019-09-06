#include "server.h"

// off_t lseek(int fildes, off_t offset, int whence);
// ssize_t recv(int socket, void *buffer, size_t length, int flags);

// STOR
//  125, 150
//  (110)
//  226, 250
//  425, 426, 451, 551, 552
//  532, 450, 452, 553
//  500, 501, 421, 530

void		put_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf_stat;
	char		*line;
	int			ret;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0 || fstat(fd, &buf_stat) < 0)
	{
		return(send_to_user_ctrl(user, RESP_550));
	}
	log_data_str("Recieving", filename);
	while ((ret = get_next_line_crlf(user->data_sock, &line)) > 0)
	{
		log_data_nbr("Bytes recieved", ft_strlen(line));
		ft_putendl_fd(line, fd);
		ft_strdel(&line);
	}
	if (close(fd) < 0)
		return(send_to_user_ctrl(user, RESP_451));
	if (ret < 0)
		return(send_to_user_ctrl(user, RESP_451));
	close_data_channel(user);
	return(send_to_user_ctrl(user, RESP_226));
}

void		cmd_stor(t_user *user, char **cmd)
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
	log_info_str("Preparing to recieve", cmd[1]);
	put_file(user, cmd[1]);
	send_to_user_ctrl(user, RESP_226);
	close_data_channel(user);
}
