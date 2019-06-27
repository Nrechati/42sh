/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_suffix_prefix.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:49:33 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/27 17:17:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	suffix_match(t_parameter *param, char *to_search, char *to_find)
{
	int		diff;

	diff = ft_strlen(to_search) - ft_strlen(to_find);
	if (ft_strequ(to_search + diff, to_find) == TRUE)
		ft_asprintf(&param->expanded, "%.*s", diff, to_search);
	else
		param->expanded = ft_strdup(to_search);
}

void	preffix_match(t_parameter *param, char *to_search, char *to_find)
{
	int		diff;

	diff = ft_strlen(to_find);
	if (ft_strnequ(to_search, to_find, diff))
		ft_asprintf(&param->expanded, "%s", to_search + diff);
	else
		param->expanded = ft_strdup(to_search);
}

int		suffix_expansion(t_list *intern, t_parameter *param)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = param->tokens->next->next->data;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		param->expanded = ft_strdup("");
	else if ((data = get_var(intern, parameter->data)) == NULL)
		param->expanded = ft_strdup("");
	else
		suffix_match(param, data, word->data);
	return (0);
}

int		prefix_expansion(t_list *intern, t_parameter *param)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = param->tokens->next->next->data;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		param->expanded = ft_strdup("");
	else if ((data = get_var(intern, parameter->data)) == NULL)
		param->expanded = ft_strdup("");
	else
		preffix_match(param, data, word->data);
	return (0);
}
