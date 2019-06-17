#include "sh21.h"

size_t	get_maxlen(size_t ref, size_t len)
{
	return (ref >= len ? ref: len);
}

uint8_t	is_cmd_delimiter(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

char	*active_completion(char *input, char *completion,
					enum e_result_type type)
{
	int		i;

	if (input == NULL || completion == NULL)
		return (NULL);
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != completion[i])
			return (ft_strdup(completion + i));
	}
	return (NULL);
}

char	*print_possibilities(char **result_tab)
{
	while (*result_tab != NULL)
		ft_putendl(*result_tab++);
}

char	*autocompletion(char *input, t_registry *shell,
								int col, uint64_t option)
{
	enum e_rsult_type			type;
	char						*input_completion;
	static t_autocomplete		result;
	static t_completion_fct		get_completion[] = {
												get_completion_cmd,
												get_completion_var,
												get_completion_var,
												get_completion_file};

	input_completion = NULL;
	if ((option & RESET_RESULT) || (option & NEW_SEARCH))
	{
		ft_freetab(&result.result_tab);
		result.nb = 0;
		result.max_len = 0;
		result.type = CMD_TYPE;
		if (option & RESET_RESULT)
			return (NULL);
	}
	if (option & NEW_SEARCH)
	{
		result.type = get_result_type(input);
		input = get_start_input(input, type);
		get_completion[type](input, &result, shell);
		if (result.nb == 1)
			return (active_completion(input + 1,
						result.type == VARIABLE_BRACKET_TYPE
						? result.tab[0] + 2 : result.tab[0] + 1);
		print_possibilities(result.result_tab);
	}
	return (NULL);
}
