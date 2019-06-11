/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:51:14 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 10:27:38 by nrechati         ###   ########.fr       */
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
int8_t		get_process_type(t_registry *shell, t_process *process);
char		**generate_env(t_registry *shell, t_list *local_env);

int8_t		setup_pipe(t_list *processess);
void		*group_to_job(void *data);
void		*cmd_to_process(void *data);
void		*action_to_redirects(void *data);

void		*token_to_var(void *data);
char		*token_to_str(void *data);

void		del_group(void *data);
void		del_command(void *data);
void		del_action(void *data);
#endif
