/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:31:52 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 19:31:54 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_list	**ptr_to_job_lst(t_list **job_lst, uint8_t mode)
{
	static t_list		**saved = NULL;

	if (mode == SET_ADDR)
		saved = job_lst;
	else if (mode == GET_ADDR)
		return (saved);
	return (NULL);
}
