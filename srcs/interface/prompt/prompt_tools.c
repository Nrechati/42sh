/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:49:32 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 10:53:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "sh21.h"

uint64_t	get_prompt_length(t_prompt *prompt)
{
//	prompt_length();
	return (vct_len(prompt->text));
}

void	expand_prompt(t_registry *shell, t_vector *text)
{
	int64_t	length;
	int64_t	index;

	index = -1;
	length = vct_len(text);
	while (index < length)
	{
		length = vct_len(text);
		++index;
		if (vct_get_string(text)[index] != '\\')
			continue ;
		++index;
		if (vct_charat(text, index) == P_NAME)
			p_insert_name(text, index - 1);
		else if (vct_charat(text, index) == P_USER)
			p_insert_username(shell, text, index - 1);
		else if (vct_charat(text, index) == P_CWD)
			p_insert_cwd(shell, text, index - 1);
		else if (vct_charat(text, index) == P_HOST)
			p_insert_host(shell, text, index - 1);
		else if (vct_charat(text, index) == P_ESCAPE)
			p_insert_escape(text, index);
//		else if (vct_charat(text, index) == P_MISS)
//			p_insert_missing(text, index - 1);
	}
}

void			prompt_mode(t_prompt *prompt, char *state, char *missing)
{
	prompt->state = state;
	prompt->missing_char = missing;
}

inline void		print_prompt(t_registry *shell, char *state)
{
	t_vector	*ptext;

	ptext = NULL;

	ptext = vct_dups(get_intern_var(shell, state));
	if (ptext == NULL)
		ptext = vct_dups("[ 42sh ]-> ");
	else
		expand_prompt(shell, ptext);
	shell->interface.prompt.text = ptext;
	print_to_window(&shell->interface, ptext);
}
