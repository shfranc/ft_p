/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:14 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/20 20:49:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		read_line_crlf(int fd, char *buf, int len)
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
			start = stop + ft_strlen(END_OF_MESG);
		}
		else
		{
			ft_putstr_fd(start, fd);
			break ;
		}
	}
}

int				read_data_ascii(int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	log_info("ASCII mode");
	total = 0;
	while ((ret = read(g_client.data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		read_line_crlf(fd, buf, ret);
		total += ret;
	}
	log_info_nb("Total bytes", total);
	if (ret < 0)
		log_error("Error reading data from data channel");
	if (fd != 0 && close(fd) < 0)
		log_error("Error closing the file");
	return (ret < 0 ? ret : total);
}

int				read_data_bin(int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	total = 0;
	log_info("BIN mode");
	while ((ret = read(g_client.data_sock, &buf, BUF_SIZE - 1)) >= 0)
	{
		total += ret;
		write(fd, buf, ret);
		if (ret == 0)
			break ;
	}
	log_info_nb("Total bytes", total);
	if (ret < 0)
		log_error("Error reading data from data channel");
	if (fd != STDOUT_FILENO && close(fd) < 0)
		log_error("Error closing the file");
	return (ret < 0 ? ret : total);
}
