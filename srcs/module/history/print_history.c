#include "sh21.h"

static int	get_elem(t_history *history, char *elem, int *first, int *last)
{
	char	*cur;
	int		fd;

	fd = 1;
	if (elem != NULL && (cur = ft_strstr(elem, "first:")) != NULL)
	{
		*first = ft_atoi(cur + 6);
		if (*first <= 0)
			*first = history->nb_of_entries + *first + 1;
		if (*first > history->nb_of_entries)
			*first = history->nb_of_entries;
	}
	else
		*first = history->nb_of_entries - 15;
	if (elem != NULL && (cur = ft_strstr(elem, "last:")) != NULL)
	{
		*last = ft_atoi(cur + 5);
		if (*last <= 0)
			*last = -(*last);
		if (*last > history->nb_of_entries)
			*last = history->nb_of_entries;
	}
	else
		*last = history->nb_of_entries;
	if (elem != NULL && (cur = ft_strstr(elem, "fd:")) != NULL)
		fd = ft_atoi(cur + 3);
	return (fd);	
}

t_entry		*entry_roll_back(t_entry *entry)
{
	while (entry != NULL)
	{
		if (entry->prev == NULL)
			return (entry);
		entry = entry->prev;
	}
	return (entry);
}

void		print_reverse(t_history *history, int first, int last,
				uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = history->nb_of_entries;
	entry = history->entry;
	while (entry != NULL && i >= first)
	{
		if (i <= last && entry->cmd != NULL)
		{
			if (option & PRINT_ID)
				ft_printf("%d\t%s\n", i, entry->cmd);
			else if (option & WITHOUT_SPACE)
				ft_printf("%s\n", entry->cmd);
			else
				ft_printf("\t%s\n", entry->cmd);
		}
		entry = entry->prev;
		i--;
	}
}

void		print_standard(t_history *history, int first, int last,
				uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = 1;
	entry = entry_roll_back(history->entry);
	while (entry != NULL && i <= last)
	{
		if (i >= first && entry->cmd != NULL)
		{
			if (option & PRINT_ID)
				ft_printf("%d\t%s\n", i, entry->cmd);
			else if (option & WITHOUT_SPACE)
				ft_printf("%s\n", entry->cmd);
			else
				ft_printf("\t%s\n", entry->cmd);
		}
		entry = entry->next;
		i++;
	}
}

void		int_swap(int *nb1, int *nb2)
{
	int		tmp;

	tmp = *nb1;
	*nb1 = *nb2;
	*nb2 = tmp;
}

void		print_history(t_history *history, char *elem, uint64_t option)
{
	int		first;
	int		last;
	int		fd;

	fd = get_elem(history, elem, &first, &last);
	if (last < first)
	{
		option |= REVERSE;
		int_swap(&first, &last);
	}
	if (option & REVERSE)
		print_reverse(history, first, last, option);
	else
		print_standard(history, first, last, option);
}
