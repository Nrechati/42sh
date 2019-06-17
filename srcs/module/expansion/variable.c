/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/17 17:04:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char	*variable_replace(t_list *lst, t_vector *str, uint32_t start_idx)
{
	char		*data;
	uint32_t	i;

	char *sub = ft_strsub(vct_get_string(str),
					start_idx + 1,
					vct_len(str) - (start_idx + 1));
//	ft_printf("SUB:|%s|\n", sub);

	i = ft_strcspn(sub, EXP_INTERUPT);

	char *data_name = ft_strsub(sub, 0, i);
//	ft_printf("data:|%s|\n", data_name);

	data = get_var(lst, data_name);

	ft_printf("Replacing |%s| from %lu to %lu with |%s|\n",
					vct_get_string(str), start_idx,
					start_idx + i + 1,
					data);

	vct_replace_string(str, start_idx, start_idx + i + 1, data);

//	ft_printf("Vector: |%s|\n", vct_get_string(str));

	char *result = ft_strdup(vct_get_string(str));
//	ft_printf("Result: |%s|\n", result);
	return (result);
}

static char	*variable_concat(t_list *lst, char **str, int i)
{
	char	*expanded;
	char	*holder;

	holder = NULL;

	t_vector *string = vct_dups(*str);


	expanded = variable_replace(lst, string, i);

//	ft_strdel(&expanded);
//	ft_strdel(str);
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

char		*variable_expansion(t_list *intern_var, char **str)
{
	t_quote		quote;
	uint32_t	i;
	uint32_t	len;

	i = 0;
	quote = 0;
	len = ft_strlen(*str);

	while (i < len)
	{
//		ft_printf("Handling char: |%c|\n", (*str)[i]);
		if (ft_strchr("\'\"", (*str)[i]))
			quote = select_quoting(quote, (*str)[i]);

		if (check_expansion(intern_var, str, i, quote) == 1)
		{
			len = ft_strlen(*str);
			break ;
		}

		++i;
	}
	return (NULL);
}
