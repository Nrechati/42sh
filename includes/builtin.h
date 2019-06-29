/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:30:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/28 10:25:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
*****************************************************
****************** ---- COMMON ---- *****************
*****************************************************
*/

t_option	set_options(char ***av, t_get_option get_option);
uint8_t		multi_strchr(char *search, char *target);

/*
*****************************************************
************************ PWD ************************
*****************************************************
*/

uint8_t		pwd_blt(t_registry *shell, char **av);
t_option	get_option_pwd(char *s, t_option option);
char		*get_pwd(t_registry *shell, t_option option);

/*
*****************************************************
*********************** ECHO ************************
*****************************************************
*/

uint8_t		echo_blt(t_registry *shell, char **av);

/*
*****************************************************
************************ CD *************************
*****************************************************
*/

uint8_t		cd_blt(t_registry *shell, char **av);
t_option	get_option_cd(char *s, t_option option);
char		*concat_pwd_with_curpath(t_registry *shell, char **path);
char		*get_home_path(void);
char		*is_cdpath_env(t_registry *shell, const char *to_find);
char		*get_relative_path(char **curpath);
char		*make_curpath_simple(char *curpath);
uint8_t		one_only_arg(char **arg);
uint8_t		check_path(t_registry *shell, char *curpath,
					const char *path_give_by_user);
uint8_t		exit_cd(t_registry *shell, char **old_pwd,
					char **curpath, uint8_t ret);

/*
*****************************************************
*********************** EXIT ************************
*****************************************************
*/

uint8_t		exit_blt(t_registry *reg, char **av);

/*
*****************************************************
*********************** TYPE ************************
*****************************************************
*/

uint8_t		type_blt(t_registry *shell, char **av);
t_option	get_option_type(char *s, t_option option);

/*
*****************************************************
*********************** HASH ************************
*****************************************************
*/

int			hash_get_opt(int i, char **av, t_option *opt);
void 		hash_builtin(t_registry *shell);
void		hash_print_help(void);
uint8_t		hash_blt(t_registry *reg, char **av);
int8_t		hash_args(t_registry *shell, char *key);
int8_t		hash_all_path(t_registry *shell);
int8_t		hash_one(t_registry *shell, char *key, char *path);

/*
*****************************************************
********************** EXPORT ***********************
*****************************************************
*/

uint8_t		export_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** SET *************************
*****************************************************
*/

uint8_t		set_blt(t_registry *shell, char **av);

/*
*****************************************************
********************** UNSET ************************
*****************************************************
*/

uint8_t		unset_blt(t_registry *shell, char **av);

/*
*****************************************************
********************** UNSET ************************
*****************************************************
*/

uint8_t		test_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** FC **************************
*****************************************************
*/

t_option	get_option_fc(char *s, t_option option);
uint8_t		fc_blt(t_registry *shell, char **av);
uint8_t		fc_list(char **av, t_option option);
uint8_t		fc_redo(t_registry *shell, char **av);
uint8_t		fc_editor(t_registry *shell, char **av, char *editor);
int8_t		get_first_last(char **av, char **param);

/*
*****************************************************
************************ BG *************************
*****************************************************
*/

uint8_t		bg_blt(t_registry *shell, char **av);

/*
*****************************************************
************************ FG *************************
*****************************************************
*/

uint8_t		fg_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** JOBS ************************
*****************************************************
*/

uint8_t		jobs_blt(t_registry *shell, char **av);
t_option	get_option_jobs(char *s, t_option option);

#endif
