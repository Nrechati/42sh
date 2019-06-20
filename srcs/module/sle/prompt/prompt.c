/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 11:24:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Standart prompt invocation
*/

void				backslash_calling(t_vector *line, t_registry *shell)
{
	t_vector	*new_input;

	new_input = vct_new(0);
	sle(shell, &new_input, SLE_PS2_PROMPT | PRINT_NL);
	vct_ncat(line, new_input, vct_len(new_input));
	vct_del(&new_input);
}

t_vector	*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];
	uint64_t	backslash;

	update_window(sle);
	print_prompt(shell, sle);
	ft_bzero(character, READ_SIZE + 1);
	vct_reset(sle->line);
	vct_reset(sle->window.displayed_line);
	backslash = 0;
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
		{
			ft_printf("\n");
			return (prompt(shell, sle));
		}
		if (character[0] == '\\')
			backslash++;
		handle_input_key(sle, character);
		redraw(shell, sle);
		if (is_eof(vct_get_string(sle->line)) == TRUE)
			break ;
	}
	ft_printf("\n");
	if (backslash % 2 == 1
			&& vct_charat(sle->line, vct_len(sle->line) - 1) == '\\')
		backslash_calling(sle->line, shell);
	if (sle->prompt.state == INT_PS1)
		vct_add(sle->line, '\n');
	if (sle->search_mode == TRUE)
	{
		sle->search_mode = FALSE;
		sle->line = sle->search_line;
	}
	history(shell, NULL, RESET_HEAD);
	return (vct_dup(sle->line));
}

t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag)
{
	t_vector	*linesave;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	prompt(shell, sle);
	sle->line = linesave;
	if (is_eof(vct_get_string(sle->sub_line)) == TRUE)
		return (NULL);
	sle_flag &= ~SLE_PS2_PROMPT;
	if (sle_flag == PRINT_BRACE)
		vct_add(sle->sub_line, ' ');
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
	return (vct_dup(sle->sub_line));
}
