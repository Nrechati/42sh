#include "sh21.h"

static enum e_result_type	get_variable_type(char *input)
{
	size_t	last_char_index;

	last_char_index = ft_strlen(input) - 1;
	if (last_char_index <= 0)
		return (FILE_TYPE);
	if (input[last_char_index] == '$')
		return (VARIABLE_TYPE);
	if (last_char_index > 0 && input[last_char_index] == '{')
		if (get_variable_type(input - 1) == VARIABLE_TYPE)
			return (VARIABLE_BRACKET_TYPE);
	return (FILE_TYPE);
}

enum e_result_type			get_result_type(char *input)
{
	if (input == NULL || *input == '\0')
		return (CMD_TYPE);
	if (is_cmd_delimiter(*input) == TRUE)
		return (get_result_type(input + 1));
	return (get_variable_type(input));
}
