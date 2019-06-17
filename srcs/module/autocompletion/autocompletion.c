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

char	*active_completion(char *input, char *completion)
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

void	print_possibilities(t_list *result)
{
	while (result != NULL)
	{
		ft_putendl((char *)result->data);
		result = result->next;
	}
}

int		lst_strcmp(void *data1, void *data2)
{
	return (ft_strcmp((char *)data1, (char *)data2));
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
		result.type = get_result_type(input);
		input = get_start_input(input, result.type);
		get_completion[result.type](input, &result, shell);
		if (result.nb == 1)
		{
			completion = (char *)result.list->data;
			return (active_completion(input + 1,
						result.type == VARIABLE_BRACKET_TYPE
						? completion + 2 : completion + 1));
		}
		ft_mergesort(&result.list, lst_strcmp);
		print_possibilities(result.list);
	}
	return (NULL);
}
