/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:21:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/18 11:29:21 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
/*
static void		debug_autocompletion(t_autocomplete *result, char *input,  ////DEBUG
					char *completion)
{
	ft_printf("\ninput: '%s', modif_input: '%s', type: '", input, completion);
	if (result->type == 0)
		ft_printf("CMD'\n");
	else if (result->type == 3)
		ft_printf("FILE'\n");
	else
		ft_printf("VAR'\n");
}*/

static char	*active_completion(char *input, char *completion)
{
	int		i;

	if (input == NULL || completion == NULL)
		return (NULL);
	i = 0;
	while (completion[i] != '\0')
	{
		if (input[i] != completion[i])
		{
			ft_strdel(&input);
			return (ft_strdup(completion + i));
		}
		i++;
	}
	return (NULL);
}

static char	*send_rest(t_autocomplete *result, char *input)
{
	char	*completion;
	
	completion = (char *)result->list->data;
	if (result->type == VARIABLE_BRACKET_TYPE)
		completion += 2;
	else if (result->type == VARIABLE_TYPE)
		completion++;
//	ft_printf("completion: %s, input: %s\n", completion, input);
	return (active_completion(input, completion));
}

static char		*get_completion(char *input, t_registry *shell,
					t_autocomplete *result, char **completion)
{
	static t_completion_fct		*get_completion[] = {get_completion_cmd,
									get_completion_var, get_completion_var,
									get_completion_file};

	result->type = get_result_type(input);
	*completion = get_start_input(input, result->type);
	*completion = get_home_input(*completion, shell);
	if (slash_is_missing(*completion) == TRUE)
	{
		ft_strdel(completion);
		*completion = ft_strdup("/");
		return (*completion);
	}
	get_completion[result->type](*completion, result, shell);
	return (NULL);
}

char		*autocompletion(char *input, t_registry *shell,
								int col, uint64_t option)
{
	char						*completion;
	static t_autocomplete		result;

	completion = NULL;
	if ((option & RESET_RESULT) || (option & NEW_SEARCH))
	{
		ft_lstdel(&result.list, NULL); // IS GOOD ?
		ft_bzero(&result, sizeof(t_autocomplete));
		if (option & RESET_RESULT)
			return (NULL);
	}
	if (get_completion(input, shell, &result, &completion) != NULL)
		return (completion);
//	debug_autocompletion(&result, input, completion); // DEBUG
	if (result.nb == 1)
		return (send_rest(&result, completion));
	ft_mergesort(&result.list, lst_strcmp);
	print_possibilities(&result, col);
	ft_strdel(&completion);
	return (NULL);
}
