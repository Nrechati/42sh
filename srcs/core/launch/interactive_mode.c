/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/04 17:39:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static uint8_t		is_input_valid(uint8_t valid)
{
	if (valid != SUCCESS && valid != LINE_FAIL)
		return (FALSE);
	return (TRUE);
}

int8_t				do_history_exp(t_vector **input)
{
	t_vector	*new;
	int8_t		ret;

	new = vct_dup(*input);
	history(NULL, NULL, RESET_HEAD);
	ret = history_expansion(new);
	history(NULL, NULL, RESET_HEAD);
	if (ret == SUCCESS)
	{
		if (ft_strequ(new->buffer, (*input)->buffer) == FALSE)
			ft_putstr(new->buffer);
		vct_del(input);
		*input = vct_dup(new);
	}
	else
		vct_del(input);
	vct_del(&new);
	return (ret);
}

void				interactive_mode(t_registry *shell)
{
	t_vector		*input;

	input = NULL;
	load_signal_profile(SLE_PROFILE);
	while (is_input_valid(sle(shell, &input, SLE_GET_INPUT)) == TRUE)
	{
		if (input != NULL && input->buffer != NULL && *input->buffer != '\0')
		{
			if (do_history_exp(&input) == FAILURE)
				continue ;
			term_mode(TERMMODE_DFLT);
			load_signal_profile(DFLT_PROFILE);
			execution_pipeline(shell, &input);
			load_signal_profile(SLE_PROFILE);
		}
		else
			vct_del(&input);
	}
	term_mode(TERMMODE_DFLT);
	shell_exit_routine(shell, SUCCESS);
}
