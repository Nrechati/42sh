/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:36:34 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 13:22:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void						sle_error(uint64_t report)
{
	if (report & CRITICAL_ERROR)
		ft_printf("42sh: One or more critical error occured: \n");
	else if (report != 0)
		ft_printf("42sh: warning: some errors occured: \n");
	if (report != 0)
		ft_printf("Error code: %lu. See logs.\n", report);
}

static uint64_t				init_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	ft_memset(&shell->interface, 0, sizeof(t_interface));
	report |= get_terminal_info(shell);
	report |= load_terminal_mode(shell);
	report |= init_termcaps(&shell->interface.termcaps);
	return (report);
}

static uint64_t				load_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	report |= assign_keycodes(&shell->interface);
	report |= link_keys_functions(shell->interface.tc_call);
	report |= set_interface_internals(shell);
	report |= init_line(&shell->interface);
	ft_memset(&shell->interface.window, 0, sizeof(t_window));
	ft_memset(&shell->interface.cursor, 0, sizeof(t_cursor));
	ft_memset(&shell->interface.prompt, 0, sizeof(t_prompt));
	report |= init_window(shell);
	report |= init_cursor(&shell->interface);
	report |= init_prompt(&shell->interface);
	return (report);
}

static uint64_t				load_interface_modules(t_interface *interface)
{
	uint64_t		report;

	report = 0;
	(void)interface;
//	report |= load_history();
//	report |= load_autocomp();
	return (report);
}

uint64_t				sle_setup(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	report |= init_interface(shell);
	/////////////////////// MOVE TO SLE INIT
	report |= load_interface(shell);
	report |= load_interface_modules(&shell->interface);
	///////////////////////////////////
	sle_error(report);
	return (report);
}
