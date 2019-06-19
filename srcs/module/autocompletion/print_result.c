#include "sh21.h"

void	post_process(t_autocomplete *result)
{
	t_list	*lst;
	char	*data;
	char	*new_data;

	lst = result->list;
	while (lst != NULL)
	{
		new_data = NULL;
		data = (char *)lst->data;
		ft_asprintf(&new_data, "%-*s", result->max_len, data);
		ft_strdel(&data);
		lst->data = (void *)new_data;
		lst = lst->next;
	}
}

static size_t	get_elem_by_line(t_autocomplete *result, int col)
{
	size_t	elem_by_line;

	if (col <= 0 || result->max_len <= 0)
		return (1);
	elem_by_line = col / result->max_len;
	if (elem_by_line == 0)
		return (1);
	return (elem_by_line);
}

static size_t	get_elem_by_col(t_autocomplete *result, int elem_by_line)
{
	size_t		elem_by_col;

	elem_by_col = result->nb / elem_by_line;
	if (result->nb % elem_by_line)
		elem_by_col++;
	return (elem_by_col);
}

void		print_possibilities(t_autocomplete *result, int col)
{
	t_list		*tmp;
	t_list		*lst;
	size_t		i;
	size_t		j;
	size_t		elem_by_col;
	size_t		elem_by_line;

	result->max_len++;
	if (result->list == NULL || result->nb == 0)
		return ;
	post_process(result);
	elem_by_line = get_elem_by_line(result, col);
	elem_by_col = get_elem_by_col(result, elem_by_line);
	ft_putchar('\n');
	lst = result->list;
	i = 0;
	while (i < elem_by_col)
	{
		tmp = lst;
		j = i;
		while (j && tmp)
		{
			tmp = tmp->next;
			j--;
		}
		while (tmp != NULL)
		{
			if (j++ % elem_by_col == 0)
				ft_putstr((char *)tmp->data);
			tmp = tmp->next;
		}
		i++;
		if (i != elem_by_col)
			ft_putchar('\n');
	}
}
