/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 10:20:01 by skuppers         ###   ########.fr       */
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
	if (set_term_mode(shell) == FAILURE)
		ft_printf("Failed to set term mode.\n");
	while (is_input_valid(sle_getinput(shell, &input)) == TRUE)
	{
		execution_pipeline(shell, input);
		vct_del(&input);
	}
	if (unset_term_mode(shell) == FAILURE)
		ft_printf("Failed to unset term mode.\n");
}
