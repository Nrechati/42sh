/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:45:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/21 02:10:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCTL_H
# define JOBCTL_H
#include "struct.h"

void	jobctl(t_registry *shell, pid_t job_pgid, uint8_t flag);

#endif
