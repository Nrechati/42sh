/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 11:57:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void				prompt_pre_process(t_sle *sle)
{
	sle->state = STATE_STD;
	vct_reset(sle->line);
	vct_reset(sle->sub_line);
	vct_reset(sle->window.displayed_line);
	history(NULL, NULL, RESET_HEAD);
	update_window(sle);
}

static int8_t			prompt_post_process(t_registry *shell, t_sle *sle)
{
	sle->state = STATE_STD;
	history(NULL, NULL, RESET_HEAD);
	vct_add(sle->line, '\n');
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);
	ft_putendl("");
	if (ft_strequ(sle->prompt.state, INT_PS1) == TRUE)
	{
		if (verif_line(sle->line) == FALSE)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_vector				*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];

	prompt_pre_process(sle);
	ft_bzero(character, READ_SIZE + 1);
	print_prompt(shell, sle);
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (is_eof(vct_get_string(sle->line)) == TRUE)
		{
			ft_putchar('\n');
			return (NULL);
		}
		if (read(0, character, READ_SIZE) == FAILURE)
			return (read_error(shell, sle));
		handle_input_key(shell, sle, character);
		redraw(shell, sle);
	}

	if (prompt_post_process(shell, sle) == FAILURE)
		vct_reset(sle->line);
	return (vct_dup(sle->line));
}

t_vector				*invoke_ps2prompt(t_registry *shell, t_sle *sle,
				uint32_t sle_flag)
{
	t_vector			*linesave;
	t_vector			*line;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE, PROMPT_MATHS,
										PROMPT_PARENTHESE, PROMPT_BRACKET};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	return (vct_dup(sle->sub_line));
}

static void					check_nl(t_registry *shell, t_sle *sl, t_vector *line)
{
	uint32_t	index;
	t_vector	*concat;
	t_vector	*hardcopy;

	(void)sl;
	index = 0;
	while (vct_charat(line, index) != '\0')
	{
		if (vct_charat(line, index) == '\\'
				&& vct_charat(line, index + 1) == '\n')
		{
			vct_pop(line);
			vct_pop(line);
			hardcopy = vct_dup(line);
			sle(shell, &concat, SLE_PS3_PROMPT);
			vct_ncat(hardcopy, concat, vct_len(concat));
			vct_replace_string(line, 0, vct_len(hardcopy),
							vct_get_string(hardcopy));
			vct_del(&hardcopy);
			vct_del(&concat);
		}
		++index;
	}
}

t_vector				*invoke_ps3prompt(t_registry *shell, t_sle *sle)
{
	t_vector	*linesave;
	t_vector	*line;

	linesave = sle->line;
	sle->line = sle->heredocln;
	sle->prompt.state = INT_PS3;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	check_nl(shell, sle, sle->heredocln);
	return (vct_dup(sle->heredocln));
}
