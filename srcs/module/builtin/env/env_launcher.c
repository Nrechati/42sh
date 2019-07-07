/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:26:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 20:39:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		run_env(t_process *process)
{
	t_process	tmp;

	ft_bzero(&tmp, sizeof(t_process));
	tmp.av = process->av;
	tmp.pgid = process->pgid;
	get_process_type(g_shell, &tmp);
	fork_process(&tmp);
	process->pid = waitpid(-1, &process->status, 0);
	process->completed = 1;
}
