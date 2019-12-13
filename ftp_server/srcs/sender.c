/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:40:55 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:51:33 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void			send_content_bin(t_user *user, const void *ptr, size_t size)
{
	size_t	count;
	int		ret;

	logger_nb(LOG_INFO, "Size", size);
	count = 0;
	while (count < size)
	{
		if ((ret = send(user->data_sock, ptr, size, 0)) == -1)
			return (send_to_user_ctrl(user, RESP_451));
		count += ret;
		logger_nb(LOG_INFO, "Bytes sent", count);
		logger_nb(LOG_DATA, "Progress...", (count / size) * 100);
	}
	send_to_user_ctrl(user, RESP_226);
}

void				send_data_bin(t_user *user, int fd, size_t size)
{
	void		*ptr;

	logger(LOG_DATA, "BIN mode", NULL);
	ptr = NULL;
	if ((ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (send_to_user_ctrl(user, RESP_451));
	logger(LOG_DATA, "Sending file", NULL);
	send_content_bin(user, ptr, size);
	if (munmap(ptr, size) < 0)
		return (send_to_user_ctrl(user, RESP_451));
	if (close(fd) < 0)
		return (send_to_user_ctrl(user, RESP_451));
}

void				send_data_ascii(t_user *user, int fd, size_t size)
{
	char	*line;
	int		ret;
	int		len;
	size_t	count;

	logger(LOG_DATA, "ASCII mode", NULL);
	logger(LOG_DATA, "Sending file", NULL);
	logger_nb(LOG_INFO, "Size", size);
	count = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		len = ft_strlen(line);
		if (send(user->data_sock, line, len, 0) == -1)
			return (send_to_user_ctrl(user, RESP_451));
		if (send(user->data_sock, END_OF_MESG, 2, 0) == -1)
			return (send_to_user_ctrl(user, RESP_451));
		count += len + 2;
	}
	logger_nb(LOG_DATA, "Bytes sent", count);
	ft_strdel(&line);
	if (ret < 0)
		return (send_to_user_ctrl(user, RESP_451));
	send_to_user_ctrl(user, RESP_226);
}
