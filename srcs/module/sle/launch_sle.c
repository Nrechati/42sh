/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 15:13:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

// TODO redraw modes FPTP / FSTP / FPTE

uint8_t		launch_sle(t_registry *shell)
{
	static uint64_t setup_report;

	if ((setup_report & SETUP_DONE) == FALSE)
		setup_report = sle_setup(shell);

	if (setup_report & CRITICAL_ERROR)
		return (CRITICAL_ERROR);

	if (set_term_mode(shell) == FAILURE)
		return (CRITICAL_ERROR);

	return (SUCCESS);
}

uint8_t		sle_getinput(t_registry *shell, t_vector **in)
{
	uint8_t	procedure_success;

	procedure_success = launch_sle(shell);
	if (procedure_success & CRITICAL_ERROR)
		return (CRITICAL_ERROR);

	*in = prompt(shell, INT_PS1);

	if (*in == NULL)
		return (FAILURE); // read fail / Malloc fail
	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);
	if (is_eof(vct_get_string(*in)))
		return (FAILURE);

	return (SUCCESS);
}
