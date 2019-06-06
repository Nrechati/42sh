/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 20:07:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

// TODO redraw modes FPTP / FSTP / FPTE

uint8_t		launch_sle(t_registry *shell, t_sle *sle)
{
	static uint64_t		setup_report = 0;

	if ((setup_report & SETUP_DONE) == FALSE)
	{
		setup_report = sle_setup(shell, sle);
		if (setup_report & CRITICAL_ERROR)
			return (CRITICAL_ERROR);
		if (set_term_mode(sle) == FAILURE)
			return (CRITICAL_ERROR);
	}
	if (shell != NULL)
	{
		sle->interns.ps1 = vct_dups(get_var(shell->intern, INT_PS1));
		sle->interns.ps2 = vct_dups(get_var(shell->intern, INT_PS2));
		sle->interns.ps3 = vct_dups(get_var(shell->intern, INT_PS3));
		sle->interns.pwd = vct_dups(get_var(shell->intern, "PWD"));
		sle->interns.username = vct_dups(get_var(shell->intern, "USER"));
		sle->interns.home = vct_dups(get_var(shell->intern, "HOME"));
	}
	return (SUCCESS);
}

uint8_t		sle(t_registry *shell, t_vector **in, uint32_t sle_flag)
{
	static t_sle sle;


	if (launch_sle(shell, &sle) == CRITICAL_ERROR)
		return (CRITICAL_ERROR);

	if (sle_flag == SLE_GET_INPUT)
	{
		sle.prompt.state = INT_PS1;
		*in = prompt(shell, &sle);

		if (*in == NULL)
			return (FAILURE);
		if (ft_strequ(vct_get_string(*in), "\0"))
			return (LINE_FAIL);
		if (is_eof(vct_get_string(*in)))
			return (FAILURE);
	}
	else if (sle_flag == SLE_EXIT)
		sle_teardown(&sle);


	else if (sle_flag & SLE_PS2_PROMPT)
		*in = invoke_ps2prompt(shell, &sle, sle_flag);
	else if (sle_flag & SLE_PS3_PROMPT)
		*in = invoke_ps3prompt(shell, &sle);
	else if (sle_flag & SLE_SIZE_UPDATE)
		redraw_window(&sle);
	return (SUCCESS);
}
