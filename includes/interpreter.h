/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:51:14 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/11 16:03:42 by cempassi         ###   ########.fr       */
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
void		run_builtin(t_registry *shell, t_process *process);
int8_t		get_process_type(t_registry *shell, t_process *process);
char		**generate_env(t_registry *shell, t_list *local_env);

void		execute_process(t_registry *shell, t_process *process, char **env);
void		fork_process(t_registry *shell, t_process *process);

int			redirect_or_other(void *action, __unused void *data);
void		close_redirects(void *data);
void		do_redirect(void *data);

int8_t		setup_pipe(t_list *processess);
void		*group_to_job(void *context, void *data);

void		update_pid(t_list *processes, pid_t pid);
uint8_t		all_is_done(t_list *processes);
int8_t		waiter(t_job *job);


void		*token_to_var(void *context, void *data);
char		*token_to_str(void *data);

void		del_group(void *data);
void		del_command(void *data);
void		del_action(void *data);
void		del_redirects(void *data);
void		del_process(void *data);

void		print_process(void *data);
void		print_job(void *data);

#endif
