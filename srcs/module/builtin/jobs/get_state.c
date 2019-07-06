/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:01:21 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/04 14:20:30 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	state_to_str(t_job *job, char **str)
{
	*str = ft_strnew(32);
	if (job_is_completed(job) == TRUE)
		ft_strcpy(*str, "Done");
	else if (job_is_stopped(job) == TRUE)
		ft_strcpy(*str, "Suspended");
	else
		ft_strcpy(*str, "Running");
}
