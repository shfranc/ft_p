/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_response.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:32:11 by sfranc            #+#    #+#             */
/*   Updated: 2019/12/13 16:32:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_reply			parse_response(char *response)
{
	if (!response || !*response)
		return (RESP_ERROR);
	if (*response == '1' || *response == '2' || *response == '3')
		return (RESP_SUCCESS);
	else if (*response == '4' || *response == '5')
		return (RESP_FAILURE);
	else
		return (RESP_ERROR);
}
