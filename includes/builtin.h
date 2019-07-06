/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:30:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 17:47:29 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "struct.h"

/*
*****************************************************
****************** ---- COMMON ---- *****************
*****************************************************
*/

t_option	set_options(char ***av, t_get_option get_option);
uint8_t		is_valid_variable(char *name);

/*
*****************************************************
************************ PWD ************************
*****************************************************
*/

uint8_t		pwd_blt(t_registry *shell, char **av, t_process *process);
t_option	get_option_pwd(char *s, t_option option);
char		*get_pwd(t_registry *shell, t_option option);

/*
*****************************************************
*********************** ECHO ************************
*****************************************************
*/

uint8_t		echo_blt(t_registry *shell, char **av, t_process *process);

/*
*****************************************************
************************ CD *************************
*****************************************************
*/

uint8_t		cd_blt(t_registry *shell, char **av, t_process *process);
t_option	get_option_cd(char *s, t_option option);
char		*concat_pwd_with_curpath(t_registry *shell, char **path);
char		*get_home_path(t_registry *shell);
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

uint8_t		exit_blt(t_registry *reg, char **av, t_process *process);

/*
*****************************************************
*********************** TYPE ************************
*****************************************************
*/

uint8_t		type_blt(t_registry *shell, char **av, t_process *process);
t_option	get_option_type(char *s, t_option option);

/*
*****************************************************
*********************** HASH ************************
*****************************************************
*/

int			hash_get_opt(int i, char **av, t_option *opt);
void		hash_builtin(t_registry *shell);
uint8_t		hash_print_help(void);
uint8_t		hash_blt(t_registry *reg, char **av, t_process *process);
int8_t		hash_args(t_registry *shell, char *key);
int8_t		hash_all_path(t_registry *shell);
int8_t		hash_one(t_registry *shell, char *key, char *path);

/*
*****************************************************
********************** EXPORT ***********************
*****************************************************
*/

uint8_t		export_blt(t_registry *shell, char **av, t_process *process);

/*
*****************************************************
*********************** SET *************************
*****************************************************
*/

uint8_t		set_blt(t_registry *shell, char **av, t_process *process);

/*
*****************************************************
********************** UNSET ************************
*****************************************************
*/

uint8_t		unset_blt(t_registry *shell, char **av, t_process *process);

/*
*****************************************************
********************** UNSET ************************
*****************************************************
*/

int8_t		test_blt(t_registry *shell, char **av, t_process *process);
uint8_t		test_not(uint8_t status);
int8_t		test_single_arg(char *arg);
int8_t		two_arg_input(t_hash *callbacks, char **av);
int8_t		three_arg_input(t_hash *callbacks, char **av);
uint8_t		test_u_cb(void *data, void *more, uint8_t type);
uint8_t		test_g_cb(void *data, void *more, uint8_t type);
uint8_t		test_r_cb(void *data, void *more, uint8_t type);
uint8_t		test_w_cb(void *data, void *more, uint8_t type);
uint8_t		test_x_cb(void *data, void *more, uint8_t type);
uint8_t		test_caps_s_cb(void *data, void *more, uint8_t type);
uint8_t		test_caps_l_cb(void *data, void *more, uint8_t type);
uint8_t		test_b_cb(void *data, void *more, uint8_t type);
uint8_t		test_p_cb(void *data, void *more, uint8_t type);
uint8_t		test_c_cb(void *data, void *more, uint8_t type);
uint8_t		test_f_cb(void *data, void *more, uint8_t type);
uint8_t		test_d_cb(void *data, void *more, uint8_t type);
uint8_t		test_e_cb(void *data, void *more, uint8_t type);
uint8_t		test_s_cb(void *data, void *more, uint8_t type);
uint8_t		test_z_cb(void *data, void *more, uint8_t type);
uint8_t		test_equal_cb(void *data, void *more, uint8_t type);
uint8_t		test_diff_cb(void *data, void *more, uint8_t type);
uint8_t		test_eq_cb(void *data, void *more, uint8_t type);
uint8_t		test_ne_cb(void *data, void *more, uint8_t type);
uint8_t		test_gt_cb(void *data, void *more, uint8_t type);
uint8_t		test_ge_cb(void *data, void *more, uint8_t type);
uint8_t		test_lt_cb(void *data, void *more, uint8_t type);
uint8_t		test_le_cb(void *data, void *more, uint8_t type);

/*
*****************************************************
************************ ENV ************************
*****************************************************
*/

uint8_t		env_blt(t_registry *shell, char **av, t_process *process);
uint8_t		setenv_blt(t_registry *shell, char **av, t_process *process);
uint8_t		unsetenv_blt(t_registry *shell, char **av, t_process *process);

#endif
