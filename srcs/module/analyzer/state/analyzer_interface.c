/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 14:04:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		check_token(t_resolution *resolve)
{
	if (resolve->token.type == E_SEMICOLON)
		return (0);
	if (resolve->token.type == E_PIPE)
		return (0);
	if (resolve->token.type == E_END)
		return (0);
	if (resolve->token.type == E_NEWLINE)
		return (0);
	return (1);
}

void	error_analyzer(t_resolution *resolve)
{
	resolve->state = P_ERROR;
	resolve->valid = -1;
	ft_strdel(&resolve->token.data);
	while (check_token(resolve))
	{
		get_token(resolve);
		ft_strdel(&resolve->token.data);
	}
	resolve->token.type = E_DEFAULT;
	ft_lstdel(&resolve->process.fd, close_fd);
}

void	separator_analyzer(t_resolution *resolve)
{
	resolve->state = P_SEPARATOR;
}

void	stop_analyzer(t_resolution *resolve)
{
	t_list		*node;

	resolve->state = P_STOP;
	if (resolve->special_case & VALID_PROCESS)
	{
		resolve->special_case ^= VALID_PROCESS;
		node = ft_lstnew(&resolve->process, sizeof(t_process));
		ft_lstaddback(&resolve->job.process_list, node);
		node = ft_lstnew(&resolve->job, sizeof(t_job));
		ft_lstaddback(&resolve->job_list, node);
		resolve->valid = 1;
	}
	resolve->token.type = E_DEFAULT;
}

void	end_analyzer(t_resolution *resolve)
{
	t_list		*node;

	resolve->state = P_END;
	if (resolve->special_case & VALID_PROCESS)
	{
		resolve->special_case ^= VALID_PROCESS;
		node = ft_lstnew(&resolve->process, sizeof(t_process));
		ft_lstaddback(&resolve->job.process_list, node);
		node = ft_lstnew(&resolve->job, sizeof(t_job));
		ft_lstaddback(&resolve->job_list, node);
		resolve->valid = 1;
	}
	get_token(resolve);
}
