/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:21:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 19:24:08 by skuppers         ###   ########.fr       */
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

static char	*active_completion(char *input, char *completion, t_registry *shell)
{
	int		i;
	char	*tmp;

	if (input == NULL || completion == NULL || *completion == '\0')
		return (NULL);
	i = 0;
	tmp = input;
	if (input[0] == '~')
		input = get_home_input(input, shell);
	while (input != '\0' && input[0] != completion[0])
		input++;
	while (completion[i] != '\0')
	{
		if (input[i] != completion[i])
		{
//			ft_strdel(&tmp);
			return (ft_strdup(completion + i));
		}
		i++;
	}
//	ft_strdel(&tmp);
	return (NULL);
}

static char	*send_rest(t_autocomplete *result, char *input, t_registry *shell)
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
//		ft_strdel(completion);
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
//		ft_lstdel(&result.list, NULL); // IS GOOD ?
		ft_bzero(&result, sizeof(t_autocomplete));
		if (option & RESET_RESULT)
			return (NULL);
	}
	if (get_completion(input, shell, &result, &completion) != NULL)
		return (completion);
	if (result.nb == 1)
		return (send_rest(&result, completion, shell));
	ft_mergesort(&result.list, lst_strcmp);
	print_possibilities(&result, col);
//	ft_strdel(&completion);
	return (NULL);
}
