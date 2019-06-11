/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/11 11:49:27 by skuppers         ###   ########.fr       */
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
# include "sle.h"
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
int8_t			set_environment(t_registry *shell, char **av, char **env);
int8_t			shell_usage(void);
void			shell_exit_routine(t_registry *shell);
int8_t			parse_arg(char **av, t_opt *option);
void			generate_grammar(void); // TEMP

/*
*****************************************************
*********************** LAUNCH **********************
*****************************************************
*/

void			launch_shell(t_registry *shell);
void			batch_mode(t_registry *shell);
void			interactive_mode(t_registry *shell);
int8_t			execution_pipeline(t_registry *shell, t_vector *input);

/*
*****************************************************
*********************** VAR *************************
*****************************************************
*/

char			*get_var(t_list *intern, char *name);
int8_t			add_var(t_list **intern, char *name, char *data, t_option flag);
int8_t			add_nbr_var(t_list **intern, char *name,
						int data, t_option flag);
size_t			list_export_size(t_list *lst);
void			print_lst(t_list *lst, int fd, char *prefix, t_option flag);
int8_t			create_node(t_list **alst, const char *var, const char *data,
					t_option flag);
int8_t			change_node(t_list **alst, const char *var, char *data,
					t_option flag);
int				find_var(void *data, void *to_find);
int8_t			free_var(t_list **alst, const char *var);

/*
*****************************************************
******************* PATH & BINARIES *****************
*****************************************************
*/

int8_t					find_in_path(t_registry *shell, char *bin, char **buf);

/*
*****************************************************
**************** LIST FUNCTION POINTERS **************
*****************************************************
*/

void			free_node(void *node);
void			close_fd(void *data);
void			delete_process(void *data);
void			delete_job(void *data);
void			del_token(void *token);

#endif
