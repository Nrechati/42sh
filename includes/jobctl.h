/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:45:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 14:09:18 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCTL_H
# define JOBCTL_H
#include "struct.h"

void	jobctl(t_registry *shell, t_job *job, uint8_t flag);

void	update_jobinfos(t_registry *shell);
void	push_current_job(t_registry *shell, t_list *job);
void	pop_current_job(t_registry *shell, t_job *job);
void	remove_job_from_list(t_list **joblst, t_job *job);
void	remove_done_jobs(t_registry *shell);


void	print_jobs(t_registry *shell, t_job *job, uint8_t flag);
void	av_to_str(t_process);
void	state_to_str(t_job *job, char **str);
void	get_job_av(t_job *job, char **str);
void	get_process_av(t_process *proc, char **str);
int8_t	parse_jobid(t_job **job, char *param);
#endif
