#include "sh21.h"

static char	*get_start_input_variable(char *input, size_t len, char c)
{
	while (len != 0)
	{
		if (input[len] == c)
			return (input + len);
		len--;
	}
	return (input);
}

static char	*get_start_input_cmd(char *input, size_t len)
{
	while (len != 0)
	{
		if (is_cmd_delimiter(*input) == TRUE)
			return (input + len);
		len--;
	}
	return (input);
}

char		*get_start_input(char *input, enum e_result_type type)
{
	size_t	last_char_pos;
	size_t	len;

	if (input == NULL)
		return (NULL);
	len = ft_strlen(input);
	if (len <= 1)
		return (input);
	last_char_pos = len - 1;
	if (type == CMD)
		return (get_start_input_cmd(input, last_char_pos));
	else if (type == VARIABLE_TYPE)
		return (get_start_input_variable(input, last_char_pos, '$'));
	else if (type == VARIABLE_BRACKET_TYPE)
		return (get_start_input_variable(input, last_char_pos, '{'));
	return (get_start_input_file(input, last_char_pos));
}
