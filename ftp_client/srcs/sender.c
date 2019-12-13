/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:16 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:42:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void			send_content_bin(const void *ptr, size_t size)
{
	size_t	count;
	int		ret;

	log_info_nb("Size", size);
	count = 0;
	while (count < size)
	{
		if ((ret = send(g_client.data_sock, ptr, size, 0)) == -1)
			return (log_error("Error sending data"));
		count += ret;
		log_info_nb("Bytes sent", count);
		log_info_nb("Progress...", (count / size) * 100);
	}
}

void				send_data_bin(int fd, size_t size)
{
	void		*ptr;

	log_info("BIN mode");
	log_info("Sending file");
	ptr = NULL;
	if ((ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (log_error("Error sending data"));
	send_content_bin(ptr, size);
	if (munmap(ptr, size) < 0)
		return (log_error("Error sending data"));
	if (close(fd) < 0)
		return (log_error("Error sending data"));
}

void				send_data_ascii(int fd, size_t size)
{
	char	*line;
	int		ret;
	int		len;
	size_t	count;

	log_info("ASCII mode");
	log_info("Sending file");
	log_info_nb("Size", size);
	count = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		len = ft_strlen(line);
		if (send(g_client.data_sock, line, len, 0) == -1)
			return (log_error("Error sending data"));
		if (send(g_client.data_sock, END_OF_MESG, 2, 0) == -1)
			return (log_error("Error sending data"));
		count += len + 2;
	}
	ft_strdel(&line);
	log_info_nb("Bytes sent", count);
	if (ret < 0)
		return (log_error("Error sending data"));
}
