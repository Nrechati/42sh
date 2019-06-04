/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:43:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 10:52:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

void						interface_error(uint64_t report)
{
	(void)report;
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

uint64_t				setup_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	report |= init_interface(shell);
	report |= load_interface(shell);
	report |= load_interface_modules(&shell->interface);
	interface_error(report);
	return (report);
}
