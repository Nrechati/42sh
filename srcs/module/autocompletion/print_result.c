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

static int	get_scale(t_autocomplete *result, int col)
{
	col = result->max_len > 0 ? col / result->max_len : 1;
	if (col < 1)
		return (1);
	return (result->nb % col > 0 ? result->nb / col + 1 : result->nb / col);
}

void		print_possibilities(t_autocomplete *result, int col)
{
	t_list		*tmp;
	t_list		*lst;
	int			i;
	int			tmp_max;
	int			max;

	if (result->list == NULL)
		return ;
	ft_putchar('\n');
	post_process(result);
	max = get_scale(result, col);
	tmp_max = 0;
	lst = result->list;
	while (tmp_max < max)
	{
		tmp = lst;
		i = tmp_max;
		while (i && tmp)
		{
			tmp = tmp->next;
			i--;
		}
		while (tmp)
		{
			if (i++ % max == 0 && tmp->data != NULL)
				ft_putstr((char *)tmp->data);
			tmp = tmp->next;
		}
		ft_putchar('\n');
		tmp_max++;
	}
}
