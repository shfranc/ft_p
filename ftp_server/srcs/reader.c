/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:42:26 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:52:00 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
			logger(LOG_INFO, ft_strsub(start, 0, stop - start), NULL);
			start = stop + ft_strlen(END_OF_MESG);
		}
		else
		{
			ft_putstr_fd(start, fd);
			break ;
		}
	}
}

void			read_data_ascii(t_user *user, int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	logger(LOG_DATA, "ASCII mode", NULL);
	total = 0;
	while ((ret = read(user->data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		read_line_crlf(fd, buf, ret);
		total += ret;
	}
	logger_nb(LOG_DATA, "Total bytes", total);
	if (close(fd) < 0)
		return (send_to_user_ctrl(user, RESP_451));
	if (ret < 0)
		return (send_to_user_ctrl(user, RESP_451));
	return (send_to_user_ctrl(user, RESP_226));
}

void			read_data_bin(t_user *user, int fd)
{
	char	buf[BUF_SIZE];
	int		total;
	int		ret;

	logger(LOG_DATA, "BIN mode", NULL);
	total = 0;
	while ((ret = read(user->data_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		total += ret;
		logger_nb(LOG_DATA, "Bytes", ret);
		write(fd, buf, ret);
	}
	logger_nb(LOG_DATA, "Total bytes", total);
	if (close(fd) < 0)
		return (send_to_user_ctrl(user, RESP_451));
	if (ret < 0)
		return (send_to_user_ctrl(user, RESP_451));
	return (send_to_user_ctrl(user, RESP_226));
}
