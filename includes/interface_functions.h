/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:54:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 13:02:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_FUNCTIONS_H
# define INTERFACE_FUNCTIONS_H

# include "struct.h"

//uint64_t				sle_setup(t_registry *shell);
//uint64_t				sle_start();
//uint64_t				sle_getinput();
//uint64_t				sle_stop();
uint64_t				setup_interface(t_registry *shell);
void					teardown_interface(t_registry *shell);
/*
*****************************************************
************** INIT / SETTING / FREE ****************
*****************************************************
*/

uint64_t	get_terminal_info(t_registry *shell);
uint64_t    load_terminal_mode(t_registry *shell);
int8_t    	set_term_mode(t_registry *shell);
int8_t   	unset_term_mode(t_registry *shell);

uint64_t	init_termcaps(t_termcaps *termcp);

uint64_t	assign_keycodes(t_interface *itf);
uint64_t    link_keys_functions(int8_t (*tc_call[AK_AMOUNT])(t_registry *shell));
uint64_t    set_interface_internals(t_registry *shell);
uint64_t    init_line(t_interface *interface);

uint64_t    init_window(t_registry *shell);
uint64_t    init_cursor(t_interface *interface);
uint64_t    init_prompt(t_interface *interface);

t_vector	*prompt(t_registry *shell, char *p_state);
t_vector	*invoke_ps2prompt(t_registry *shell, char *missing);

void		handle_input_key(t_registry *shell, char c[READ_SIZE ]);

void		add_redraw_flags(t_interface *itf, uint32_t flag);
void		set_redraw_flags(t_interface *itf, uint32_t rd_flag);
void		set_redraw_bounds(t_interface *itf, uint64_t s, uint64_t e);
void		set_cursor_pos(t_interface *itf, uint64_t index);
void		move_cursor(t_registry *shell);
void		move_cursor_to_coord(t_interface *itf, uint64_t x, uint64_t y);


void		update_window(t_registry *shell);

void		redraw(t_registry *shell);
void		redrawmode_clear(t_registry *shell);
void		redrawmode_line(t_registry *shell);
void		redrawmode_last(t_registry *shell);
void		redrawmode_fptp(t_registry *shell);
void		redrawmode_visual(t_registry *shell);
//void		redrawmode_visual_off(t_registry *shell);

void		define_interface_signals(void);
void		interface_resize_handler(const int signo);


void		print_char(t_interface *itf, char c);
void		print_loop(t_interface *itf, char *str);
void		print_prompt(t_registry *shell, char *state);
void		print_prompt_to_window(t_interface *itf, t_vector *text);




uint64_t	get_prompt_length(t_prompt *prompt);
t_coord		*index_to_coord(t_interface *itf, uint64_t indx);


void		p_insert_name(t_vector *text, uint64_t index);
void		p_insert_username(t_registry *shell, t_vector *text, uint64_t index);
void		p_insert_cwd(t_registry *shell, t_vector *text, uint64_t index);
void		p_insert_host(t_registry *shell, t_vector *text, uint64_t index);
void		p_insert_missing(t_registry *shell, t_vector *text, uint64_t index);
//void		p_insert_escape(t_vector *text, uint64_t index);

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


void		link_actions_to_keys(int8_t (*tc_call[AK_AMOUNT])
				(struct s_registry *shell));

/*
*****************************************************
********************* DISPLAY ***********************
*****************************************************
*/
/*
*****************************************************
********************* PROMPT ************************
*****************************************************
*/
/*
*****************************************************
******************** ACTION KEYS ********************
*****************************************************
*/

int8_t		ak_arrow_left(t_registry *shell);
int8_t		ak_arrow_right(t_registry *shell);
int8_t		ak_home(t_registry *shell);
int8_t		ak_end(t_registry *shell);
int8_t		ak_delete(t_registry *shell);
int8_t		ak_backspace(t_registry *shell);

int8_t		ak_ctrl_d(t_registry *shell);
int8_t		ak_ctrl_l(t_registry *shell);

int8_t		ak_ctrl_left(t_registry *shell);
int8_t		ak_ctrl_right(t_registry *shell);
int8_t		ak_ctrl_up(t_registry *shell);
int8_t		ak_ctrl_down(t_registry *shell);

int8_t		ak_enter_visual_mode(t_registry *shell);
int8_t		ak_exit_visual_mode(t_registry *shell);

int8_t		ak_arrow_up(t_registry *shell);
int8_t		ak_arrow_down(t_registry *shell);

int8_t		ak_cut_selection(t_registry *shell);
int8_t		ak_copy_selection(t_registry *shell);
int8_t		ak_paste_clipboard(t_registry *shell);

/*

int8_t		ak_cut_before_cursor(t_registry *shell);
int8_t		ak_cut_after_cursor(t_registry *shell);
int8_t		ak_copy_before_cursor(t_registry *shell);
int8_t		ak_copy_after_cursor(t_registry *shell);


int8_t		ak_hightab(t_registry *shell);
*/
#endif
