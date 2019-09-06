#include "server.h"

static void	fill_line_crlf(char *buff, char **line)
{
	char	*temp;

	if (*line)
	{
		temp = *line;
		*line = ft_strjoin(temp, buff);
		ft_strdel(&temp);
	}
	else
		*line = ft_strdup(buff);
	ft_bzero(buff, BUFF_SIZE);
}

static int	empty_buff_crlf(char *buff, char **line, off_t *offset)
{
	char	*stop;

	if (!buff || *buff == 0)
		return (0);
	if ((stop = ft_strstr(buff, END_OF_MESG)))
	{
		*stop = '\0';
		*offset += stop - buff;
		fill_line_crlf(buff, line);
		return (1);
	}
	else
		fill_line_crlf(buff, line);
	return (0);

}

int			get_next_line_crlf(int fd, char **line)
{
	static off_t	offset = 0;
	ssize_t			ret;
	char			buff[BUFF_SIZE];

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	ft_putnbr_endl(offset);
	if (offset && lseek(fd, offset, SEEK_SET) == -1)
	{
		perror("lseek");
		return (-1);
	}
	if (empty_buff_crlf(buff, line, &offset) == 1)
		return (1);
	while ((ret = read(fd, &buff, BUFF_SIZE - 1)) > 0)
	{
		if (empty_buff_crlf(buff, line, &offset) == 1)
			return (1);
	}
	if (ret == -1)
		return (-1);
	if (*line != NULL)
		return (1);
	return (0);
}
