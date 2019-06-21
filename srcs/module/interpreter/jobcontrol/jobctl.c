/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/21 04:35:12 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sh21.h"

void	print_joblist(__unused t_list *joblist, __unused uint8_t flag)
{

}

void	save_job_to_bg(__unused t_list *joblist, __unused pid_t job_pgid)
{

}

void	jobctl(__unused t_registry *shell, __unused pid_t job_pgid, uint8_t flag)
{
//	static t_list	*joblist;

	if (flag == JOBCTL_PUTINBG)
		;

	else if (flag == JOBCTL_PUTINFG)
		;

	else if (flag == JOBCTL_LIST)
		;
}
