/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_tools2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:55:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 19:14:14 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*get_home_input(char *input, t_registry *shell)
{
	char	*new_input;
	char	*var;

	if (input == NULL)
		return (NULL);
	new_input = NULL;
	while (*input == ' ' || *input == '\t' || is_cmd_delimiter(*input) == TRUE)
		input++;
	if (*input == '~' && (var = get_var(shell->intern, "HOME")) != NULL)
		ft_asprintf(&new_input, "%s%s", var, input + 1);
	else
		new_input = ft_strdup(input);
	return (new_input);
}

uint8_t			slash_is_missing(char *completion)
{
	size_t	len;

	if (completion != NULL)
	{
		len = ft_strlen(completion);
		if (len > 0 && completion[len - 1] == '.')
			return (FALSE);
		else if (*completion != '\0'
				&& (is_a_directory(completion, "\0") == TRUE)
				&& completion[ft_strlen(completion) - 1] != '/')
			return (TRUE);
	}
	return (FALSE);
}
