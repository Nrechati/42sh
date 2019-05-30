/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 19:07:16 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "libft.h"
# include "define.h"
# include "enum.h"
# include "struct.h"
# include "sig.h"
# include "builtin.h"
# include "interface_functions.h"
# include "history.h"
# include "lexer.h"
# include "parser.h"
# include "analyzer.h"
# include "resolve.h"
# include "log.h"

/*
*****************************************************
******************** INIT / EXIT ********************
*****************************************************
*/
void			free_registry(t_registry *shell);
int8_t			set_environment(t_registry *shell, char **av, char **env);
int8_t			shell_usage(void);
void			shell_exit_routine(t_registry *shell);
int8_t			parse_arg(char **av, t_opt *option);
void			generate_grammar(t_registry *shell);

/*
*****************************************************
****************** READ / INTERFACE *****************
*****************************************************
*/

char			*read_input(const int fd);
void			launch_interface(t_registry *shell);
int8_t			execution_pipeline(t_registry *shell, t_list *token_list);
void			get_prompt_ps1(t_registry *shell);

/*
*****************************************************
*********************** VAR *************************
*****************************************************
*/

char			*get_intern_var(t_registry *shell, char *name);
int8_t			add_intern_var(t_registry *shell, char *name,
						char *data, t_option flag);
int8_t			add_intern_nbr(t_registry *shell, char *name,
						int data, t_option flag);
size_t			list_export_size(t_list *lst);
void			print_lst(t_list *lst, int fd, char *prefix, t_option flag);
int8_t			create_node(t_list **alst, const char *var, const char *data,
					t_option flag);
int8_t			change_node(t_list **alst, const char *var, char *data,
					t_option flag);
char			*get_data(t_list *lst, char *var);
int				find_variable(void *data, void *to_find);

/*
*********************** FREE
*/

void			close_fd(void *data);
void			clear_node(void *node);
void			free_anode(t_list *ptr);
int8_t			del_node(t_list *ptr, const char *name);
int8_t			free_node(t_list **alst, const char *var);
void			delete_variable(void *data);
void			delete_analyzer(t_resolution *resolve);
void			delete_process(void *data);
void			delete_job(void *data);
void			del_token(void *token);

#endif
