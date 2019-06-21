
#include "sh21.h"

void	call_history(t_lexer *lexer, size_t initial_scale, uint64_t option)
{
	char	*search;
	char	*replace;
	size_t	len;

	search = NULL;
	if (lexer->input->buffer[lexer->index + initial_scale - 1] == '!')
		replace = history(NULL, NULL, option);
	else
	{
		search = get_search(lexer->input->buffer
				+ lexer->index + initial_scale);
		if (ft_isnumeric(search) == TRUE)
			replace = history(NULL, search, option | BY_ID);
		else
			replace = history(NULL, search, option | BY_NAME);
	}
	if (replace != NULL)
	{
		len = ft_strlen(search) + initial_scale;
		vct_replace_string(lexer->input, lexer->index,
				lexer->index + len, replace);
	}
	else
	{
		ft_dprintf(2, "42sh: %s: event not found", search);
		/// EXIT LEXER
	}
	history(NULL, NULL, RESET_HEAD);
	ft_strdel(&replace);
	ft_strdel(&search);
}


void	history_replace(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '!')
	{
		ft_printf("'%c'\n", get_input(lexer, NEXT_CHAR));
		if (get_input(lexer, NEXT_CHAR) == '!')
			call_history(lexer, 2, GET_ENTRY | PREV);
		else if (ft_isalnum(get_input(lexer, NEXT_CHAR)) == TRUE)
			call_history(lexer, 2, GET_ENTRY);
		else if (get_input(lexer, NEXT_CHAR) == '-'
			&& ft_isalnum(get_input(lexer, NEXT_NEXT_CHAR)) == TRUE)
			call_history(lexer, 3, GET_ENTRY | REL);
	}
}
