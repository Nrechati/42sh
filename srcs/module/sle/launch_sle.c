/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 20:41:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

uint8_t		launch_sle(t_registry *shell, t_sle *sle)
{
	static uint64_t		setup_report = 0;

	if ((setup_report & SETUP_DONE) == FALSE)
	{
		shell->option.option |= RECORD_HISTORY_OPT;
		history(shell, NULL, INIT_HISTORY);
		setup_report = sle_setup(shell, sle);
		if (setup_report & CRITICAL_ERROR)
			return (CRITICAL_ERROR);
	}
	save_intern_vars(shell, sle);
	return (SUCCESS);
}

void		handle_cc(t_registry *shell, t_sle *sl, uint32_t flag)
{
	sl->state = STATE_STD;
	set_redraw_flags(sl, RD_LINE | RD_CEND);
	redraw(shell, sl);
	vct_reset(sl->line);
	update_window(sl);
	find_multiline_coord(sl, sl->cursor.index);
	if (flag & SLE_CC)
		ft_putendl("^C");
}

static uint8_t		sle_get_input(t_registry *shell, t_sle *sle, t_vector **in)
{
	sle->prompt.state = INT_PS1;
	*in = prompt(shell, sle);
	if (*in == NULL || is_eof(vct_get_string(*in)))
	{
		vct_del(in);
		return (FAILURE);
	}
	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);
	return (SUCCESS);
}

uint8_t		sle(t_registry *shell, t_vector **in, uint32_t sle_flag)
{
	static t_sle		sle;

	if (launch_sle(shell, &sle) == CRITICAL_ERROR)
		return (CRITICAL_ERROR);
	load_signal_profile(SLE_PROFILE);
	term_mode(TERMMODE_SLE);
	if (sle_flag != SLE_SIZE_UPDATE)
		sle.state = STATE_STD;
	if (sle_flag == SLE_GET_INPUT)
		return (sle_get_input(shell, &sle, in));
	else if (sle_flag & SLE_PS2_PROMPT)
		*in = invoke_ps2prompt(shell, &sle, sle_flag);
	else if (sle_flag & SLE_PS3_PROMPT)
		*in = invoke_ps3prompt(shell, &sle);
	else if (sle_flag & SLE_RD_PROMPT)
		handle_cc(g_shell, &sle, sle_flag);
	else if (sle_flag & SLE_SIZE_UPDATE)
	{
		if (sle.state == STATE_REVSEARCH || sle.state == STATE_INCSEARCH)
		{
			vct_reset(sle.line);
			sle.state = STATE_STD;
		}
		redraw_window(&sle);
		find_multiline_coord(&sle, 0);
		set_cursor_pos(&sle, sle.cursor.index);
	}
	else if (sle_flag == SLE_EXIT)
		sle_teardown(&sle);
	return (SUCCESS);
}
