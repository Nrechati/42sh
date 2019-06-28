/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:30:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 21:05:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H
/*
*****************************************************
****************** ---- COMMON ---- *****************
*****************************************************
*/

int8_t	kill_blt(t_registry *shell, char **av);
int8_t	bg_blt(t_registry *shell, char **av);
int8_t	fg_blt(t_registry *shell, char **av);
int8_t	jobs_blt(t_registry *shell, char **av);


/*
*****************************************************
****************** ---- COMMON ---- *****************
*****************************************************
*/

t_option	set_options(char ***av, t_get_option get_option);

/*
*****************************************************
************************ PWD ************************
*****************************************************
*/

int8_t		pwd_blt(t_registry *shell, char **av);
t_option	get_option_pwd(char *s, t_option option);
char		*get_pwd(t_registry *shell, t_option option);

/*
*****************************************************
*********************** ECHO ************************
*****************************************************
*/

int8_t		echo_blt(t_registry *shell, char **av);

/*
*****************************************************
************************ CD *************************
*****************************************************
*/

int8_t		cd_blt(t_registry *shell, char **av);
t_option	get_option_cd(char *s, t_option option);
char		*concat_pwd_with_curpath(t_registry *shell, char **path);
char		*get_home_path(void);
char		*is_cdpath_env(t_registry *shell, const char *to_find);
char		*get_relative_path(char **curpath);
char		*make_curpath_simple(char *curpath);
uint8_t		one_only_arg(t_registry *shell, char **arg);
uint8_t		check_path(t_registry *shell, char *curpath,
					const char *path_give_by_user);
int8_t		exit_cd(t_registry *shell, char **old_pwd,
					char **curpath, int8_t ret);

/*
*****************************************************
*********************** ENV *************************
*****************************************************
*/

int8_t		env_blt(t_registry *shell, char **av);
t_option	get_option_env(char *s, t_option option);

/*
*****************************************************
********************** SETENV ***********************
*****************************************************
*/

int8_t		setenv_blt(t_registry *shell, char **av);

/*
*****************************************************
********************* UNSETENV **********************
*****************************************************
*/

int8_t		unsetenv_blt(t_registry *shell, char **av);

/*
*****************************************************
********************** INTERN ***********************
*****************************************************
*/

int8_t		intern_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** EXIT ************************
*****************************************************
*/

int8_t		exit_blt(t_registry *reg, char **av);

/*
*****************************************************
*********************** TYPE ************************
*****************************************************
*/

int8_t		type_blt(t_registry *shell, char **av);
t_option	get_option_type(char *s, t_option option);

/*
*****************************************************
*********************** HASH ************************
*****************************************************
*/

int			hash_get_opt(int i, char **av, t_option *opt);
void 		hash_builtin(t_registry *shell);
void		hash_print_help(void);
int8_t		hash_blt(t_registry *reg, char **av);
int8_t		hash_args(t_registry *shell, char *key);
int8_t		hash_all_path(t_registry *shell);
int8_t		hash_one(t_registry *shell, char *key, char *path);

/*
*****************************************************
********************** EXPORT ***********************
*****************************************************
*/

int8_t		export_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** SET *************************
*****************************************************
*/

int8_t		set_blt(t_registry *shell, char **av);

/*
*****************************************************
********************** UNSET ************************
*****************************************************
*/

int8_t		unset_blt(t_registry *shell, char **av);

/*
*****************************************************
*********************** FC **************************
*****************************************************
*/

t_option	get_option_fc(char *s, t_option option);
int8_t		fc_blt(t_registry *shell, char **av);
int8_t		fc_list(char **av, t_option option);
int8_t		get_first_last(char **av, char **param);
int8_t		fc_redo(t_registry *shell, char **av, t_option option);
int8_t		fc_editor(t_registry *shell, char **av, char *editor,
					t_option option);

/*
*****************************************************
*********************** JOBS ************************
*****************************************************
*/

t_option		get_option_jobs(char *s, t_option option);

#endif
