/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:51:14 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/06 18:48:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include <sys/types.h>
# include "struct.h"

/*
*****************************************************
********************** MAPING ***********************
*****************************************************
*/

int8_t 		interpreter(t_registry *shell, t_list **cmd_group);

void		*group_to_job(void *data);
void		*cmd_to_process(void *data);
void		*action_to_redirects(void *data);

void		del_group(void *data);
void		del_command(void *data);
void		del_action(void *data);
#endif
