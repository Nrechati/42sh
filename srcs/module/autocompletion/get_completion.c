#include "sh21.h"

size_t	get_size_of_var_tab(char *input, size_t len, t_list *env)
{
	size_t		nb;
	t_variable	*var;

	nb = 0;
	while (env != NULL)
	{
		var = env->data;
		if (len == 0 || ft_strnequ(var->name, input + 1, len) == TRUE)
			nb++;		
		env = env->next;
	}
	return (nb);
}



void	get_result_var_tab(char *input, size_t len, t_list *env,
							t_autocomplete *result)
{
	t_variable	*var;
	size_t		i;

	result->result_tab = ft_malloc(sizeof(char *) * (result->nb + 1));
	if (result->result_tab == NULL)
		return ;
	ft_bzero(result->result_tab, result->nb + 1);
	i = 0;
	while (env != NULL && i < result->nb)
	{
		var = env->data;
		if (len == 0 || ft_strnequ(var->name, input + 1, len) == TRUE)
		{
			if (result->type == VARIABLE_BRACKET_TYPE)
				ft_asprint(&result->result->tab[i++], "{$%s} ", var->name)
			else
				ft_asprint(&result->result->tab[i++], "$%s ", var->name)
			result->max_len = get_maxlen(result->max_len, ft_strlen(var->name));
		}
		env = env->next;
	}
	result->result_tab[i] = NULL;
}


void	get_completion_var(char *input, t_autocomplete *result, t_registry *shell)
{
	size_t		len;
	t_list		*env;

	env = shell->intern;
	len = input == NULL ? 0 : ft_strlen(input);
	result->nb = get_size_of_var_tab(input, len, env);
	if (result->nb == 0)
		return (NULL);
	get_result_var_tab(input, len, env, result);
}

void get_completion_cmd(char *input, t_autocomplete *result, t_registry *shell)
{
	(void)input;	
	(void)result;	
	(void)shell;	
}

void get_completion_file(char *input, t_autocomplete *result, t_registry *shell)
{
	(void)input;	
	(void)result;	
	(void)shell;	
}

