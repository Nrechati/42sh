/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/30 09:07:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t		is_input_valid(uint8_t valid)
{
	if (valid != SUCCESS && valid != LINE_FAIL)
		return (FALSE);
	return (TRUE);
}

void				interactive_mode(t_registry *shell)
{
	t_vector		*input;

	input = NULL;
	load_signal_profile(SLE_PROFILE);
	while (is_input_valid(sle(shell, &input, SLE_GET_INPUT)) == TRUE)
	{
		term_mode(TERMMODE_DFLT);
		load_signal_profile(DFLT_PROFILE);
		if (history_expansion(input) == SUCCESS)
		{
			history(NULL, NULL, RESET_HEAD);
			execution_pipeline(shell, &input);
		}
		load_signal_profile(SLE_PROFILE);
		vct_del(&input);
	}
}
