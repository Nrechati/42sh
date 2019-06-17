#include "sh21.h"

void	get_completion_var(char *input,
					t_autocomplete *result, t_registry *shell)
{
	t_list		*env;
	t_variable	*var;
	char		*data;
	size_t		len;

	result->nb = 0;
	len = input == NULL ? 0 : ft_strlen(input);
	env = shell->intern;
	while (env != NULL)
	{
		var = env->data;
		if ((len == 0 || ft_strnequ(var->name, input, len) == TRUE)
				&& (var->flag & SET_VAR))
		{
			data = NULL;
			if (result->type == VARIABLE_BRACKET_TYPE)
				ft_asprintf(&data, "{$%s} ", var->name);
			else
				ft_asprintf(&data, "$%s ", var->name);
			ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
			result->max_len = get_maxlen(result->max_len, ft_strlen(data));
			ft_strdel(&data);
			result->nb++;
		}
		env = env->next;
	}
}
