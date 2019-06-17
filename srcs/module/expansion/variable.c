/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 18:39:32 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char	*variable_replace(t_list *lst, t_vector *str, uint32_t start_idx)
{
	uint32_t	i;
	char 		*sub;
	char		*data;
	char		*data_name;

	sub	= ft_strsub(vct_get_string(str),
					start_idx + 1,
					vct_len(str) - (start_idx + 1));
	i = ft_strcspn(sub, EXP_INTERUPT);
	data_name = ft_strsub(sub, 0, i);
	data = get_var(lst, data_name);
	ft_strdel(&sub);
	ft_strdel(&data_name);
	if (data == NULL)
		data = "";
	vct_replace_string(str, start_idx, start_idx + i + 1, data);
	sub = ft_strdup(vct_get_string(str));
	return (sub);
}

static char	*variable_concat(t_list *lst, char **str, int i)
{
	t_vector	*string;
	char		*expanded;

	string = vct_dups(*str);
	ft_strdel(str);
	expanded = variable_replace(lst, string, i);
	vct_del(&string);
	return (expanded);
}

static int	check_expansion(t_list *intern_var, char **str, int i, t_quote quote)
{
	int		check;

	check = 0;
	if ((*str)[i] == '$' && (*str)[i + 1] != '\0')
	{
		if (ft_strchr(EXP_INTERUPT, (*str)[i + 1]))
			check = 0;
		else if (quote != QUOTE_SINGLE)
		{
			*str = variable_concat(intern_var, str, i);
			check = 1;
		}
	}
	return (check);
}

void		variable_expansion(t_list *intern_var, char **str)
{
	uint32_t	i;
	uint32_t	len;
	t_quote		quote;

	i = 0;
	quote = 0;
	len = ft_strlen(*str);
	while (i < len)
	{
		if (ft_strchr("\'\"", (*str)[i]))
			quote = select_quoting(quote, (*str)[i]);
		if (check_expansion(intern_var, str, i, quote) == 1)
			len = ft_strlen(*str);
		++i;
	}
}
