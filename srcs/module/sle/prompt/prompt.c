/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 13:55:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

# define ANY 0x0001

void		subprompt_call(t_registry *shell, t_sle *sle, uint64_t option)
{
	t_vector	*new_input;

	new_input = invoke_ps2prompt(shell, sle, option);
	vct_ncat(sle->line, new_input, vct_len(new_input));
	vct_del(&new_input);
}

void		verif_char(t_registry *shell, t_sle *sle, size_t i, uint16_t close)
{
	if (close == ANY)
	{
		if (vct_charat(sle->line, i) == '\\'
			&& vct_charat(sle->line, i + 1) == '\n'
			&& vct_charat(sle->line, i + 2) == '\0')
		{
			vct_pop(sle->line);
			vct_pop(sle->line);
			ft_putchar('\n');
			subprompt_call(shell, sle, PRINT_NL);
		}
	}
}

void	verif_line(t_registry *shell, t_sle *sle, uint16_t close)
{
	size_t	i;
	char	c;

	i = 0;
	while ((c = vct_charat(sle->line, i)) != '\0')
	{
		verif_char(shell, sle, i, close);
		i++;
	}

}

t_vector	*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];

	sle->state = STATE_STD;
	ft_bzero(character, READ_SIZE + 1);
	vct_reset(sle->line);
	vct_reset(sle->window.displayed_line);
	history(shell, NULL, RESET_HEAD);
	update_window(sle);
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
	if (sle->state == STATE_SEARCH)
		sle->line = sle->search_line;
	if (ft_strequ(vct_get_string(sle->line), "Failed") == TRUE)
		vct_reset(sle->line);
	sle->state = STATE_STD;
	autocompletion(NULL, shell, sle->window.cols, RESET_RESULT);
	history(shell, NULL, RESET_HEAD);
	vct_add(sle->line, '\n');
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);
	if (sle->prompt.state == INT_PS1)
	{
		verif_line(shell, sle, ANY);
		ft_putendl(sle->line->buffer);
	}
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
//	if (sle_flag != PRINT_NL)
//		vct_add(sle->line, '\n');
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
