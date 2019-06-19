/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/18 11:38:22 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Standart prompt invocation
*/

t_vector	*prompt(t_registry *shell, t_sle *sle)
{
	char	character[READ_SIZE + 1];


	ft_bzero(character, READ_SIZE + 1);
	vct_reset(sle->line);
	vct_reset(sle->window.displayed_line);
	history(shell, NULL, RESET_HEAD);

	sle->state = STATE_STD;

	update_window(sle);

	print_prompt(shell, sle);
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
		{
			ft_printf("\nRead failed\n");
			return (NULL);
		handle_input_key(shell, sle, character);
		redraw(shell, sle);

		if (is_eof(vct_get_string(sle->line)) == TRUE)
			break ;
	}


	if (sle->state == STATE_SEARCH)
		sle->line = sle->search_line;
	if (ft_strequ(vct_get_string(sle->line), "Failed") == TRUE)
		vct_reset(sle->line);
	sle->state = STATE_STD;
	autocompletion(NULL, shell, sle->window.cols, RESET_RESULT);
	history(shell, NULL, RESET_HEAD);
//	vct_add(sle->line, '\n');

	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);


	ft_printf("\n");

	return (vct_dup(sle->line));
}

t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag)
{
	t_vector	*linesave;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	prompt(shell, sle);
	sle->line = linesave;
	if (is_eof(vct_get_string(sle->sub_line)) == TRUE)
		return (NULL);
//	vct_add(sle->sub_line, '\n');
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
//	vct_add(sle->sub_line, '\n');
	return (vct_dup(sle->sub_line));
}
