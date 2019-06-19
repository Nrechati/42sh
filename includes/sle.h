/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:37:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 12:56:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_FUNCTIONS_H
# define INTERFACE_FUNCTIONS_H

# include "struct.h"

/*
*****************************************************
************** INIT / SETTING / FREE ****************
*****************************************************
*/

uint8_t		sle(t_registry *shell, t_vector **input, uint32_t sle_flag);

uint64_t	sle_setup(t_registry *shell, t_sle *sle);
void		sle_teardown(t_sle *sle);

uint64_t	get_terminal_info(t_registry *shell);
uint64_t	init_termcaps(t_termcaps *termcp);
uint64_t	assign_keycodes(t_sle *sle);
uint64_t    link_keys_functions(int8_t (*actionkeys[AK_AMOUNT])(__unused t_registry *shell, t_sle *sle));
uint64_t    set_sle_internals(t_registry *shell);
uint64_t    init_line(t_sle *sle);

uint64_t    init_window(t_sle *sle);
uint64_t    init_cursor(t_sle *sle);
uint64_t    init_prompt(t_sle *sle);

t_vector	*prompt(t_registry *shell, t_sle *sle);
t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag);
t_vector	*invoke_ps3prompt(t_registry *shell, t_sle *sle);

void		handle_input_key(t_registry *shell, t_sle *sle, char c[READ_SIZE ]);

void		add_redraw_flags(t_sle *sle, uint32_t flag);
void		set_redraw_flags(t_sle *sle, uint32_t rd_flag);
void		set_redraw_bounds(t_sle *sle, uint64_t s, uint64_t e);
void		set_cursor_pos(t_sle *sle, uint64_t index);
void		move_cursor(t_sle *sle);
void		move_cursor_to_coord(t_sle *sle, uint64_t x, uint64_t y);


void		update_window(t_sle *sle);
void		redraw_window(t_sle *sle);

void		redraw(t_registry *shell, t_sle *sle);
void		redrawmode_clear(t_registry *shell, t_sle *sle);
void		redrawmode_line(t_sle *sle);
void		redrawmode_last(t_sle *sle);
void		redrawmode_fptp(t_sle *sle);
void		redrawmode_fstp(t_sle *sle);
void		redrawmode_fpte(t_sle *sle);
void		redrawmode_visual(t_sle *sle);
//void		redrawmode_visual_off(t_sle *sle);

void		define_interface_signals(void);
void		interface_resize_handler(const int signo);


void		print_char(t_sle *sle, char c);
void		print_loop(t_sle *sle, char *str);
void		print_prompt(t_registry *shell, t_sle *sle);
void		print_prompt_to_window(t_sle *sle, t_vector *text);




uint64_t	get_prompt_length(t_prompt *prompt);
void		index_to_coord(t_sle *sle, uint64_t indx, t_coord *co);


void		p_insert_name(t_vector *text, uint64_t index);
void		p_insert_username(t_sle *sle, t_vector *text, uint64_t index);
void		p_insert_cwd(t_sle *sle, t_vector *text, uint64_t index);
void		p_insert_host(t_vector *text, uint64_t index);
void		p_insert_missing(t_sle *sle, t_vector *text, uint64_t index);

/*
*****************************************************
********************  UTILS *************************
*****************************************************
*/


int			ft_putc(const int c);
uint8_t		is_eof(const char *buffer);
uint8_t		is_separator(char[READ_SIZE + 1]);
uint8_t		is_printable(char c[READ_SIZE + 1]);
uint64_t	compute_mask(char c[READ_SIZE]);

uint32_t	get_next_char(const char *str, uint32_t index, const char direction);


void		link_actions_to_keys(int8_t (*actionkeys[AK_AMOUNT])
				(struct s_sle *sle));

/*
*****************************************************
******************** ACTION KEYS ********************
*****************************************************
*/

int8_t		ak_arrow_up(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_down(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_left(t_registry *shell, t_sle *sle);
int8_t		ak_arrow_right(t_registry *shell, t_sle *sle);
int8_t		ak_home(t_registry *shell, t_sle *sle);
int8_t		ak_end(t_registry *shell, t_sle *sle);
int8_t		ak_delete(t_registry *shell, t_sle *sle);
int8_t		ak_backspace(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_d(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_l(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_left(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_right(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_up(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_down(t_registry *shell, t_sle *sle);

int8_t		ak_ctrl_r(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_i(t_registry *shell, t_sle *sle);
int8_t		ak_enter_visual_mode(t_registry *shell, t_sle *sle);
int8_t		ak_exit_modes(t_registry *shell, t_sle *sle);

int8_t		ak_cut_selection(t_registry *shell, t_sle *sle);
int8_t		ak_copy_selection(t_registry *shell, t_sle *sle);
int8_t		ak_paste_clipboard(t_registry *shell, t_sle *sle);

int8_t		ak_hightab(t_registry *shell, t_sle *sle);
int8_t		ak_ctrl_t(t_sle *sle);
#endif
