/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function_pointers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:07:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 13:47:11 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

void	del_token(void *token)
{
	t_token *tmp;

	tmp = token;
	ft_strdel(&tmp->data);
}

void	delete_process(void *data)
{
	t_process	*process;

	process = (t_process *)data;
	ft_freetab(&process->av);
}

void	delete_job(void *data)
{
	(void)data;
//	t_job	*job;

//	job = (t_job *)data;
}
