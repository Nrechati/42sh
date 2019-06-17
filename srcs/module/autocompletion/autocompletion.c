/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:21:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/17 17:21:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char	*active_completion(char *input, char *completion)
{
	int		i;

	if (input == NULL || completion == NULL)
		return (NULL);
	i = 0;
	while (completion[i] != '\0')
	{
		if (input[i] != completion[i])
			return (ft_strdup(completion + i));
		i++;
	}
	return (NULL);
}

char	*autocompletion(char *input, t_registry *shell,
								int col, uint64_t option)
{
	char						*completion;
	static t_autocomplete		result;
	static t_completion_fct		*get_completion[] = {
												get_completion_cmd,
												get_completion_var,
												get_completion_var,
												get_completion_file};

	(void)col;
	completion = NULL;
	if ((option & RESET_RESULT) || (option & NEW_SEARCH))
	{
		ft_lstdel(&result.list, NULL); // IS GOOD ?
		ft_bzero(&result, (sizeof(result)));
		if (option & RESET_RESULT)
			return (NULL);
	}
	if (option & NEW_SEARCH)
	{
		result.type = get_result_type(input, input == NULL ? 0 : ft_strlen(input));
		completion = get_start_input(input, result.type) + 1;
		//ft_printf("\ninput: '%s', modif_input: '%s', type: %d\n", input, completion, result.type);
		get_completion[result.type](completion, &result, shell);
		if (result.nb == 1)
		{
			input = completion;
			completion = (char *)result.list->data;
			completion += result.type == VARIABLE_BRACKET_TYPE ? 2 : 1;
			return (active_completion(input, completion));
		}
		ft_mergesort(&result.list, lst_strcmp);
		print_possibilities(&result, col);
	}
	return (NULL);
}
