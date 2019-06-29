/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:01:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 22:29:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void state_to_str(uint8_t state, char **str)
{
	*str = ft_strnew(32);

	if (state == PENDING)
		ft_strcpy(*str, "Pending");
	else if (state == RUNNING)
		ft_strcpy(*str, "Running");
	else if (state == STOPPED)
		ft_strcpy(*str, "Stopped");
	else if (state & ENDED)
		ft_strcpy(*str, "Done");
	else
		ft_strcpy(*str, "Unknown");
}