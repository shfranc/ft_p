#include "server.h"

void		read_line_crlf(int fd, char *buf, int len)
{
	char	*start;
	char	*stop;

	start = buf;
	while (start < buf + len)
	{
		if ((stop = ft_strstr(start, END_OF_MESG)))
		{
			write(fd, start, stop - start);
			write(fd, "\n", 1);
			log_info(ft_strsub(start, 0, stop - start));
			start = stop + ft_strlen(END_OF_MESG);
		}
		else
		{
			ft_putstr_fd(start, fd);
			break ;
		}
	}
}

void		read_data_ascii(t_user *user, int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	log_data("ASCII mode");
	total = 0;
	while ((ret = read(user->data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		read_line_crlf(fd, buf, ret);
		total += ret;
	}
	log_data_nbr("Total bytes", total);
	if (close(fd) < 0)
		return(send_to_user_ctrl(user, RESP_451));
	if (ret < 0)
		return(send_to_user_ctrl(user, RESP_451));
	return(send_to_user_ctrl(user, RESP_226));
}

void		read_data_bin(t_user *user, int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	log_data("BIN mode");
	total = 0;
	while ((ret = read(user->data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		total += ret;
		log_data_nbr("Bytes", ret);
		write(fd, buf, ret);
	}
	log_data_nbr("Total bytes", total);
	if (close(fd) < 0)
		return(send_to_user_ctrl(user, RESP_451));
	if (ret < 0)
		return(send_to_user_ctrl(user, RESP_451));
	return(send_to_user_ctrl(user, RESP_226));
}

void		put_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf_stat;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0 || fstat(fd, &buf_stat) < 0)
	{
		return(send_to_user_ctrl(user, RESP_451));
	}
	log_data_str("Receiving", filename);
	if (user->data_type == ASCII)
		return(read_data_ascii(user, fd));
	else if (user->data_type == BIN)
		return(read_data_bin(user, fd));
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
	log_info_str("Preparing to receive", cmd[1]);
	put_file(user, cmd[1]);
	close_data_channel(user);
}
