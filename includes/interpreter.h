/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:51:14 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/17 12:39:19 by cempassi         ###   ########.fr       */
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

void		assign_intern(t_registry *shell, t_list *assign);
void		execute_process(t_registry *shell, t_process *process, char **env);
void		fork_process(t_registry *shell, t_process *process);

void		check_redirect_error(void *context, void *data);
int			redirect_or_other(void *action, __unused void *data);
void		close_redirect(void *data);
void		do_redirect(void *data);

int8_t		setup_pipe(t_list *processess);
void		*group_to_job(void *context, void *data);

void		update_pid(t_list *processes, pid_t pid);
uint8_t		all_is_done(t_list *processes);
int8_t		waiter(t_job *job);

char		*get_filename(t_list *node);
int 		get_io(t_list *node);

void		stdout_truncate(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		stdout_append(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		stdin_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		io_append(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		io_truncate(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		io_readfile(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		close_fd(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		move_fd(t_registry *shell, t_redirect *redirect
					, t_action *action);
void		duplicate_fd(t_registry *shell, t_redirect *redirect
					, t_action *action);

void		*token_to_var(void *context, void *data);
char		*token_to_str(void *data);

void		del_group(void *data);
void		del_command(void *data);
void		del_action(void *data);
void		del_redirects(void *data);
void		del_process(void *data);

void		print_process(void *data);
void		print_job(void *data);
void		print_var_lst(void *data);

#endif
