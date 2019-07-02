/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 14:33:51 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sigstop_exec(int signo)
{
	t_list		*job_lst;

	job_lst = *ptr_to_job_lst(NULL, GET_ADDR);
	ft_lstiter_ctx(job_lst, &signo, set_signaled);
}

void	sigcont_exec(__unused int signo)
{
	//
}

// C-z
void	sigtstp_exec(__unused int signo)
{
	// put current foreground job to background
}

void	sigttin_exec(int signo)
{
	(void)signo;
}

void	sigttou_exec(int signo)
{
	(void)signo;
}

void	sigchld_exec(int signo)
{
	(void)signo;
}
