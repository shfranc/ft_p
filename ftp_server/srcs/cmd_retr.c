#include "server.h"

static void				send_content_bin(t_user *user, const void *ptr, size_t size)
{
	size_t	count;
	int		ret;

	logger_nb(LOG_INFO ,"Size", size);
	count = 0;
	while (count < size)
	{
		if ((ret = send(user->data_sock, ptr, size, 0)) == -1)
			return(send_to_user_ctrl(user, RESP_451));
		count += ret;
		logger_nb(LOG_INFO, "Bytes sent", count);
		logger_nb(LOG_DATA,  "Progress...",(count / size) * 100);
	}
	send_to_user_ctrl(user, RESP_226);
}

static void				send_data_bin(t_user *user, int fd, size_t size)
{
	void		*ptr;

	logger(LOG_DATA, "BIN mode", NULL);
	ptr = NULL;
	if ((ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return(send_to_user_ctrl(user, RESP_451));
	logger(LOG_DATA,  "Sending file", NULL);
	send_content_bin(user, ptr, size);
	if (munmap(ptr, size) < 0)
		return(send_to_user_ctrl(user, RESP_451));
	if (close(fd) < 0)
		return(send_to_user_ctrl(user, RESP_451));
}

static void				send_data_ascii(t_user *user, int fd, size_t size)
{
	char	*line;
	int		ret;
	int		len;
	size_t	count;

	logger(LOG_DATA,  "ASCII mode", NULL);
	logger(LOG_DATA,  "Sending file", NULL);
	logger_nb(LOG_INFO ,"Size", size);
	count = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		len = ft_strlen(line);
		if (send(user->data_sock, line, len, 0) == -1)
			return(send_to_user_ctrl(user, RESP_451));
		if (send(user->data_sock, END_OF_MESG, 2, 0) == -1)
			return(send_to_user_ctrl(user, RESP_451));
		count += len + 2;
	}
	logger_nb(LOG_DATA,  "Bytes sent", count);
	ft_strdel(&line);
	if (ret < 0)
		return(send_to_user_ctrl(user, RESP_451));
	send_to_user_ctrl(user, RESP_226);
}

static t_bool			check_file_path(t_user *user, char *filename)
{
	char		*virtual_path;

	logger(LOG_INFO, "Trying to fetch", filename);
	virtual_path = convert_path_real_to_virtual(filename);
	if (is_valid_path(virtual_path) == FALSE)
	{
		free(virtual_path);
		logger(LOG_INFO, "Invalid path, no get performed.", NULL);
		send_to_user_ctrl(user, RESP_550_1);
		return (FALSE);
	}
	free(virtual_path);
	return (TRUE);
}

static void 			get_file(t_user *user, char *filename)
{
	int			fd;
	struct stat buf;

	if (check_file_path(user, filename) == FALSE)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || fstat(fd, &buf) < 0)
		return(send_to_user_ctrl(user, RESP_550));
	if (user->data_type == ASCII)
		return(send_data_ascii(user, fd, buf.st_size));
	else if (user->data_type == BIN)
		return(send_data_bin(user, fd, buf.st_size));
}

void				cmd_retr(t_user *user, char **cmd)
{
	char 	*abs_virtual_path;
	char 	*real_path;

	if (ft_tablen(cmd) != 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock == -1)
		return (send_to_user_ctrl(user, RESP_426));
	else
		send_to_user_ctrl(user, RESP_125);
	logger(LOG_INFO, "Fetching", cmd[1]);
	abs_virtual_path = get_virtual_absolute_path(user, cmd[1]);
	real_path = convert_path_virtual_to_real(abs_virtual_path);
	get_file(user, real_path);
	free(abs_virtual_path);
	free(real_path);
	close_data_channel(user);
}
