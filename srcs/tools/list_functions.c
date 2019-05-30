/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:07:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:52:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

void	delete_analyzer(t_resolution *resolve)
{
	if (resolve->tmp_env != NULL)
		ft_lstdel(&resolve->tmp_env, NULL);
	if (resolve->job_list != NULL)
		ft_lstdel(&resolve->job_list, delete_job);
	ft_stckdestroy(&resolve->stack, del_token);
}
