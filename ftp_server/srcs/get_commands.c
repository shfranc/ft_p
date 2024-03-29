/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:27:02 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 15:38:48 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_command		g_commands[NB_COMMAND] =
{
	{"CWD", &cmd_cwd},
	{"EPRT", &cmd_eprt},
	{"EPSV", &cmd_epsv},
	{"LIST", &cmd_list},
	{"PASV", &cmd_pasv},
	{"PORT", &cmd_port},
	{"PWD", &cmd_pwd},
	{"RETR", &cmd_retr},
	{"STOR", &cmd_stor},
	{"TYPE", &cmd_type}
};

void			loop_commands(t_user *user, char **cmd)
{
	int		i;

	i = 0;
	while (i < NB_COMMAND && cmd[0])
	{
		if (ft_strcmp(cmd[0], g_commands[i].name) == 0)
		{
			g_commands[i].run(user, cmd);
			return ;
		}
		i++;
	}
	send_to_user_ctrl(user, RESP_500);
}

void			get_client_commands(t_user *user)
{
	int					ret;
	char				buf[BUF_SIZE];
	char				**cmd;

	while ((ret = read(user->control_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		if (buf[ret - 2] == '\r')
			buf[ret - 2] = '\0';
		else if (buf[ret - 1] == '\n')
			buf[ret - 1] = '\0';
		else
			buf[ret] = '\0';
		log_client_command(buf);
		if (ft_strcmp(buf, "QUIT") == 0)
			break ;
		cmd = ft_strsplit(buf, ' ');
		loop_commands(user, cmd);
		ft_freetab(&cmd);
	}
	if (ret == -1)
		log_error("read: Failed to read from client");
	close(user->control_sock);
	return ;
}
