/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 19:56:00 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	prompt_pre_process(t_sle *sle)
{
	sle->state = STATE_STD;
	vct_reset(sle->line);
	vct_reset(sle->window.displayed_line);
	history(NULL, NULL, RESET_HEAD);
	update_window(sle);
}

static void	prompt_post_process(t_registry *shell, t_sle *sle)
{
	if (sle->state == STATE_SEARCH)
		sle->line = sle->search_line;
	if (ft_strequ(vct_get_string(sle->line), "Failed") == TRUE)
		vct_reset(sle->line);
	sle->state = STATE_STD;
	autocompletion(NULL, shell, NULL, RESET_RESULT);
	history(NULL, NULL, RESET_HEAD);
	vct_add(sle->line, '\n');
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);
	if (ft_strequ(sle->prompt.state, INT_PS1) == TRUE
			&& (shell->option.option & INTERACTIVE_OPT) == FALSE)
		verif_line(sle);
}

t_vector	*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];

	prompt_pre_process(sle);
	ft_bzero(character, READ_SIZE + 1);
	print_prompt(shell, sle);
	while (is_separator(character) == FALSE
		 && is_eof(vct_get_string(sle->line)) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
			return (NULL);
		handle_input_key(shell, sle, character);
		redraw(shell, sle);
	}
	prompt_post_process(shell, sle);
	return (vct_dup(sle->line));
}

t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag)
{
	t_vector	*linesave;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE, PROMPT_MATHS};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	prompt(shell, sle);
	sle->line = linesave;
	if (is_eof(vct_get_string(sle->sub_line)) == TRUE)
		return (NULL);
	return (vct_dup(sle->sub_line));
}

t_vector	*invoke_ps3prompt(t_registry *shell, t_sle *sle)
{
	t_vector	*linesave;

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.state = INT_PS3;
	prompt(shell, sle);
	sle->line = linesave;
	if (is_eof(vct_get_string(sle->sub_line)) == TRUE)
		return (NULL);
	//vct_add(sle->sub_line, '\n');
	return (vct_dup(sle->sub_line));
}
