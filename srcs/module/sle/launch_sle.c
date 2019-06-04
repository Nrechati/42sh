/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 18:33:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

static uint8_t		get_input(t_registry *shell, t_vector **in)
{
	if (in == NULL)
		return (FAILURE);

	*in = prompt(shell, INT_PS1);

	if (*in == NULL)
		return (FAILURE); // read fail / Malloc fail
	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);
	if (is_eof(vct_get_string(*in)))
		return (FAILURE);
	return (SUCCESS);
}

/*
**
**	Rework to harmony with new refactor
**
*/
//void				simple_line_edit(t_regstry *shell);
void				interactive_mode(t_registry *shell)
{
	uint8_t			valid;
	t_vector		*input;

	valid = 0;
	input = NULL;

	if (set_term_mode(shell) == FAILURE)
		ft_printf("Failed to set term mode.\n");

	define_interface_signals();
	while (1)
	{
		if (valid != SUCCESS && valid != LINE_FAIL)
			return ;
		ft_dprintf(2, "\nSLE sending: |%s|\n", vct_get_string(input));
//		execution_pipeline(shell,
//				lexer(&shell->lexinfo, vct_get_string(input)));
	}

// default signals
	if (unset_term_mode(shell) == FAILURE)
		ft_printf("Failed to unset term mode.\n");
}
