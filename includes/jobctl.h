/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:45:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/25 22:42:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCTL_H
# define JOBCTL_H
#include "struct.h"

void	jobctl(t_registry *shell, t_job *job, uint8_t flag);

void	update_job_ids(t_registry *shell);
void	update_currents(t_registry *shell, t_job *job);

void	remove_job_from_active_list(t_list **joblst, t_job *job);

void	print_jobs(t_job *job, uint8_t flag);
void	av_to_str(t_process);
void	state_to_str(uint8_t state, char **str);
void	get_job_av(t_job *job, char **str);
void	get_process_av(t_process *proc, char **str);
int8_t	parse_jobid(t_job **job, char *param);
#endif
