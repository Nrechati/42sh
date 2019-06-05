/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 10:20:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static inline char		*read_input_cmd(t_registry *shell)
{
	if (shell->option.option & COMMAND_OPT)
		return (ft_strdup(shell->option.command_str));
	return (read_input(STDIN_FILENO));
}

static void				batch_mode(t_registry *shell)
{
	char	*command;

	command = read_input_cmd(shell);
	if (ft_strcheck(command, ft_isprint) == TRUE)
		execution_pipeline(shell, command);
	else
		ft_dprintf(2, "21sh: Not a valid input.\n");
	ft_strdel(&command);
}

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

	while (1)
	{
		if (is_input_valid(sle_getinput(shell, &input)) == FALSE)
			break ;
		execution_pipeline(shell, vct_get_string(input));
	}

	if (unset_term_mode(shell) == FAILURE)
		ft_printf("Failed to unset term mode.\n");
}

static inline uint8_t	is_shell_interactive(t_registry *shell)
{
	if ((shell->option.option & COMMAND_OPT) == FALSE
			&& isatty(STDIN_FILENO) != 0)
	{
		shell->option.option |= INTERACTIVE_OPT;
		return (TRUE);
	}
	return (FALSE);
}

void					launch_shell(t_registry *shell)
{
	if (is_shell_interactive(shell) == TRUE)
	{
		if ((sle_setup(shell) & CRITICAL_ERROR) == FALSE)
			interactive_mode(shell);
		sle_teardown(shell);
	}
	else
		batch_mode(shell);
}
