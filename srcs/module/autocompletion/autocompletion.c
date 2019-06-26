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

static char		*active_completion(t_autocomplete *result,
					char *input, char *completion, t_registry *shell)
{
	int		i;
	char	*start;

	if (input == NULL || completion == NULL || *completion == '\0')
		return (NULL);
	start = input + result->index;
	start = get_home_input(start, shell);
	i = 0;
	while (completion[i] != '\0')
	{
		if (start[i] != completion[i])
		{
			ft_strdel(&start);
			return (ft_strdup(completion + i));
		}
		i++;
	}
	ft_strdel(&start);
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
	return (active_completion(result, input, completion, shell));
}

static char		*get_completion(char **input, t_registry *shell,
					t_autocomplete *result, char **completion)
{
	static t_completion_fct		*get_completion[] = {get_completion_cmd,
									get_completion_var, get_completion_var,
									get_completion_file};
	char	*tmp;

	if (ft_strequ(".", *input) == TRUE)
	{
		*completion = ft_strdup("/");
		return (*completion);
	}
	result->type = get_result_type(*input);
	*completion = get_start_input(*input, result->type);
	result->index = ft_strlen(*input) - ft_strlen(*completion);
	*completion = get_home_input(*completion, shell);
	tmp = *input;
	tmp[result->index] = '\0';
	*input = ft_strjoin(tmp, *completion);
	ft_strdel(&tmp);
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
	if (get_completion(&cpy_input, shell, &result, completion) != NULL)
	{
		ft_strdel(&cpy_input);
		return (SUCCESS);
	}
	if (result.nb == 1 || result.nb == 0)
	{
		if (result.nb == 0)
		{
			ft_strdel(&cpy_input);
			return (NOT_FOUND);
		}
		*completion = send_rest(&result, cpy_input, shell);
		ft_strdel(&cpy_input);
		return (SUCCESS);
	}
	ft_mergesort(&result.list, lst_strcmp);
	print_possibilities(&result);
	ft_strdel(&cpy_input);
	ft_strdel(completion);
	return (FAILURE);
}
