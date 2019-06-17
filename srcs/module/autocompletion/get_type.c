#include "sh21.h"

enum e_result_type is_file_type(char *input, size_t len)
{
	while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t'))
		len--;
	if (len == 0 || is_cmd_delimiter(input[len - 1]) == TRUE)
		return (CMD_TYPE);
	return (FILE_TYPE);
}

enum e_result_type	get_result_type(char *input, size_t len)
{
	if (len == 0 || is_cmd_delimiter(input[len - 1]) == TRUE)
		return (CMD_TYPE);
	if (input[len - 1] == ' ' || input[len - 1] == '\t'
			|| input[len - 1] == '}' || input[len - 1] == '/')
		return (is_file_type(input, len));
	if (input[len - 1] == '$')
		return (VARIABLE_TYPE);
	if (input[len - 1] == '{')
	{
		if (get_result_type(input, --len) == VARIABLE_TYPE)
			return (VARIABLE_BRACKET_TYPE);
	}
	return (get_result_type(input, len - 1));
}
