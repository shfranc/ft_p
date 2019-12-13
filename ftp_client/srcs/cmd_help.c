/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:30:38 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:30:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			cmd_help(char *cmd)
{
	int		i;

	if (ft_strcmp(cmd, "help") != 0)
		ft_putendl("usage: help");
	i = 0;
	while (i < NB_COMMAND)
	{
		printf("%-15s %s\n", g_commands[i].name, g_commands[i].desc);
		i++;
	}
}
