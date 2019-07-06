/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:51:14 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 19:02:17 by nrechati         ###   ########.fr       */
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

void			mark_job_as_running(t_job *job);
void			mark_job_as_stopped(t_job *job);
void			mark_job_as_completed(t_job *job);

//void			run_background_job(t_registry *shell, t_job *job);

int8_t			interpreter(t_registry *shell, t_list **cmd_group);
t_list			**ptr_to_job_lst(t_list **job_lst, uint8_t mode);

void			fork_process(t_process *process);
int8_t			launch_pipeline(t_list *processess);
int				run_job(void *context, void *data);
void			run_builtin(t_process *process);
int				run_process(t_process *process);

uint8_t			job_is_completed(t_job *job);
uint8_t			job_is_stopped(t_job *job);

int8_t			get_process_type(t_registry *shell, t_process *process);
int				is_export(void *data, void *to_find);
int				copy_var(void *src, void *dest);
int				variable_update(void *context, void *data);
char			**generate_env(t_registry *shell, t_list *local_env);

int				assign_intern(t_registry *shell, t_list **assign);

int				set_process_pgid(void *context, void *data);
t_redirection	*redirecter_init(void);
int				check_redirect_error(void *context, void *data);
int				redirect_or_other(void *action, void *data);
void			del_process_redirect(void *data);
void			close_redirect(void *data);
void			close_pipe(void *data);
int				do_redirect(void *context, void *data);
int				builtin_redirect(void *context, void *data);

int				check_delimiter(char **delimiter, t_vector **vector, int fd);
void			valid_heredoc_setup(t_redirect *redirect, int from, int to);

int				setup_redirect(t_process *process);
int				get_failed_process(void *data, void *context);
void			re_open_std(const uint8_t std, char *tty_name);
uint8_t			check_job(t_job *job, int job_type);
void			set_stopped(void *data);
int				set_signaled(void *context, void *data);

void			*group_to_job(void *context, void *data);

int8_t			waiter(t_job *job);
void			set_status(t_job *job, t_process *current, int status);
int				expand_process(t_list *intern, t_process *process);

char			*get_filename(t_list *node);
void			set_ambigous_redirect(t_redirect *redirect, t_list *node);
int				get_io(t_list *node);
int				get_custom_fd(char **str, t_list *node);
void			open_write_file(t_redirect *redirect, char *filename, int flag);

void			heredoc(t_redirect *redirect, t_action *action);
void			heredoc_trim(t_redirect *redirect, t_action *action);
void			io_heredoc(t_redirect *redirect, t_action *action);
void			io_heredoc_trim(t_redirect *redirect, t_action *action);
int				write_heredoc(t_vector **vector, int fd, int trim);

void			stdout_truncate(t_redirect *redirect, t_action *action);
void			stdout_append(t_redirect *redirect, t_action *action);
void			stdin_readfile(t_redirect *redirect, t_action *action);
void			stdin_readfd(t_redirect *redirect, t_action *action);
void			io_append(t_redirect *redirect, t_action *action);
void			io_truncate(t_redirect *redirect, t_action *action);
void			io_readfile(t_redirect *redirect, t_action *action);
void			close_fd(t_redirect *redirect, t_action *action);
void			move_fd(t_redirect *redirect, t_action *action);
void			duplicate_fd(t_redirect *redirect, t_action *action);
void			io_readfd(t_redirect *redirect, t_action *action);
void			stdout_truncate_special(t_redirect *redirect, t_action *action);

void			*token_to_var(void *context, void *data);
char			*token_to_str(void *data);

void			del_group(void *data);
void			del_command(void *data);
void			del_action(void *data);
void			del_redirects(void *data);
void			del_process(void *data);
void			del_job(void *data);

void			print_signaled(char *command, int signo);
void			print_process(void *data);
void			print_job(void *data);
void			print_var_lst(void *data);

#endif
