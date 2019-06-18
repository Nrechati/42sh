/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/18 15:14:37 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

void		save_intern_vars(t_registry *shell, t_sle *sle)
{
	if (shell != NULL)
	{
		if (sle->interns.ps1 != NULL)
			vct_del(&sle->interns.ps1);
		if (sle->interns.ps2 != NULL)
			vct_del(&sle->interns.ps2);
		if (sle->interns.ps3 != NULL)
			vct_del(&sle->interns.ps3);
		if (sle->interns.pwd != NULL)
			vct_del(&sle->interns.pwd);
		if (sle->interns.username != NULL)
			vct_del(&sle->interns.username);
		if (sle->interns.home != NULL)
			vct_del(&sle->interns.home);

		sle->interns.ps1 = vct_dups(get_var(shell->intern, INT_PS1));
		sle->interns.ps2 = vct_dups(get_var(shell->intern, INT_PS2));
		sle->interns.ps3 = vct_dups(get_var(shell->intern, INT_PS3));
		sle->interns.pwd = vct_dups(get_var(shell->intern, "PWD"));
		sle->interns.username = vct_dups(get_var(shell->intern, "USER"));
		sle->interns.home = vct_dups(get_var(shell->intern, "HOME"));
	}
}

uint8_t		launch_sle(t_registry *shell, t_sle *sle)
{
	static uint64_t		setup_report = 0;

	if ((setup_report & SETUP_DONE) == FALSE)
	{
		shell->option.option |= RECORD_HISTORY;
		history(shell, NULL, INIT_HISTORY);
		setup_report = sle_setup(shell, sle);
		if (setup_report & CRITICAL_ERROR)
			return (CRITICAL_ERROR);
//		if (set_term_mode(sle) == FAILURE)
//			return (CRITICAL_ERROR);
	}
	save_intern_vars(shell, sle);
	return (SUCCESS);
}

uint8_t		sle(t_registry *shell, t_vector **in, uint32_t sle_flag)
{
	static t_sle sle;


	if (launch_sle(shell, &sle) == CRITICAL_ERROR)
		return (CRITICAL_ERROR);

//	define_interface_signals();

	term_mode(TERMMODE_SLE);
	if (sle_flag == SLE_GET_INPUT)
	{
		sle.prompt.state = INT_PS1;
		*in = prompt(shell, &sle);
		if (*in == NULL || is_eof(vct_get_string(*in)))
			return (FAILURE);
		if (ft_strequ(vct_get_string(*in), "\0"))
			return (LINE_FAIL);
	}
	else if (sle_flag & SLE_PS2_PROMPT)
		*in = invoke_ps2prompt(shell, &sle, sle_flag);
	else if (sle_flag & SLE_PS3_PROMPT)
		*in = invoke_ps3prompt(shell, &sle);

	else if (sle_flag & SLE_SIZE_UPDATE)
		redraw_window(&sle);

	else if (sle_flag == SLE_EXIT)
		sle_teardown(&sle);

	term_mode(TERMMODE_DFLT);
	return (SUCCESS);
}
