/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:46:51 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/24 17:40:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			default_expansion(t_list *intern, t_parameter *param)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = param->tokens->next->next->data;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		param->expanded = ft_strdup(word->data);
	else if ((data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			param->expanded = ft_strdup(word->data);
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

int			assign_expansion(t_list *intern, t_parameter *param)
{
	t_pex_token	*word;
	char		*data;
	int			status;

	word = param->tokens->next->next->data;
	status = get_var_status(intern, ((t_pex_token *)param->tokens->data)->data);
	if (status < 0 )
	{
		add_var(&intern, param->tokens->data, word->data, SET_VAR);
		param->expanded = ft_strdup(word->data);
	}
	else if ((data = get_var(intern, param->tokens->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
		{
			add_var(&intern, param->tokens->data, word->data, SET_VAR);
			param->expanded = ft_strdup(word->data);
		}
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

static int	error_exists(char *parameter, char *message)
{
	ft_dprintf(2, "42sh: %s: %s\n", parameter, message);
	return (-1);
}

int			exists_expansion(t_list *intern, t_parameter *param)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = param->tokens->next->next->data;
	status = get_var_status(intern, parameter->data);
	if (status < 0 )
		return (error_exists(parameter->data, word->data));
	else if ((data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			return (error_exists(parameter->data, word->data));
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

int			replace_expansion(t_list *intern, t_parameter *param)
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
	else if (status > 0 && (data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			param->expanded = ft_strdup(word->data);
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(word->data);
	return (0);
}