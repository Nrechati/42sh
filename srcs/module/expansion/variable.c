/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 03:41:27 by cempassi         ###   ########.fr       */
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

static int variable_concat(t_list *lst, char **dest, int i)
{
	t_vector	*vector;

	vector = vct_dups(*dest);
	ft_strdel(dest);
	if ((*dest = variable_replace(lst, vector, i)) == NULL)
		return (-1);
	vct_del(&vector);
	return (1);
}

static int	check_expansion(t_list *intern, char **dest, int i, t_quote quote)
{
	int		check;

	check = 0;
	if ((*dest)[i] == '$' && (*dest)[i + 1] != '\0')
	{
		if (ft_strchr(EXP_INTERUPT, (*dest)[i + 1]))
			check = 0;
		else if (quote != QUOTE_SINGLE)
			check = variable_concat(intern, dest, i);
	}
	return (check);
}

char		*variable_expansion(t_list *intern_var, char *str)
{
	uint32_t	i;
	uint32_t	len;
	t_quote		quote;
	char		*dest;
	int			result;

	i = 0;
	quote = 0;
	dest = ft_strdup(str);
	len = ft_strlen(dest);
	while (i < len)
	{
		if (ft_strchr("\'\"", dest[i]))
			quote = select_quoting(quote, dest[i]);
		if ((result = check_expansion(intern_var, &dest, i, quote)) == 1)
			len = ft_strlen(dest);
		else if (result == -1)
			return (NULL);
		++i;
	}
	return (dest);
}
