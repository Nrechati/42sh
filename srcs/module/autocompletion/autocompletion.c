/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:21:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 20:03:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char		*active_completion(char *input, char *completion,
						t_registry *shell)
{
	int		i;
	int		len;
	char	*tmp;

	if (input == NULL || completion == NULL || *completion == '\0')
		return (NULL);
	tmp = input;
	if (input[0] == '~')
		input = get_home_input(input, shell);
	i = ft_strlen(completion) - 1;
	len = ft_strlen(input) - 1;
	while (i >= 0)
	{
		if (i == 0 || input[len] == completion[i])
		{
			ft_strdel(&tmp);
			return (ft_strdup(completion + i + 1));
		}
		i--;
	}
	ft_strdel(&tmp);
	return (NULL);
}

static char		*send_rest(t_autocomplete *result, char *input,
					t_registry *shell)
{
	char	*completion;

	completion = (char *)result->list->data;
	if (result->type == VARIABLE_BRACKET_TYPE)
		completion += 2;
	else if (result->type == VARIABLE_TYPE)
		completion++;
	return (active_completion(input, completion, shell));
}

static char		*get_completion(char *input, t_registry *shell,
					t_autocomplete *result, char **completion)
{
	static t_completion_fct		*get_completion[] = {get_completion_cmd,
									get_completion_var, get_completion_var,
									get_completion_file};

	if (ft_strequ(".", input) == TRUE)
	{
		*completion = ft_strdup("/");
		return (*completion);
	}
	result->type = get_result_type(input);
	*completion = get_start_input(input, result->type);
	*completion = get_home_input(*completion, shell);
	if (result->type == FILE_TYPE && slash_is_missing(*completion) == TRUE
		&& ft_strequ(".", *completion) == FALSE)
	{
		ft_strdel(completion);
		*completion = ft_strdup("/");
		return (*completion);
	}
	get_completion[result->type](*completion, result, shell);
	return (NULL);
}

static uint8_t	init_and_reset(t_autocomplete *result, uint64_t option)
{
	if ((option & RESET_RESULT) || (option & NEW_SEARCH))
	{
		ft_lstdel(&result->list, NULL);
		ft_bzero(result, sizeof(t_autocomplete));
		if (option & RESET_RESULT)
			return (TRUE);
	}
	return (FALSE);
}

int8_t			autocompletion(char *input, t_registry *shell,
								char **completion, uint64_t option)
{
	static t_autocomplete		result;
	char						*cpy_input;

	if (init_and_reset(&result, option) == TRUE)
		return (SUCCESS);
	cpy_input = ft_strdup(input);
	if (get_completion(cpy_input, shell, &result, completion) != NULL)
	{
		ft_strdel(&cpy_input);
		return (SUCCESS);
	}
	if (result.nb == 1 || result.nb == 0)
	{
		ft_strdel(&cpy_input);
		if (result.nb == 0)
			return (NOT_FOUND);
		*completion = send_rest(&result, *completion, shell);
		return (SUCCESS);
	}
	ft_mergesort(&result.list, lst_strcmp);
	print_possibilities(&result);
	ft_strdel(&cpy_input);
	ft_strdel(completion);
	return (FAILURE);
}
