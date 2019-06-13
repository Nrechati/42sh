#include "sh21.h"

static int	get_elem(t_history *history, char *elem, int *first, int *last)
{
	char	*cur;
	int		fd;

	if (elem != NULL && (cur = ft_strstr(elem, "first:")) != NULL)
		*first = ft_atoi(cur + 6);
	else
		*first = history->nb_of_entries - 15;
	if (elem != NULL && (cur = ft_strstr(elem, "last:")) != NULL)
		*last = ft_atoi(cur + 5);
	else
		*last = history->nb_of_entries;
	if (elem != NULL && (cur = ft_strstr(elem, "fd:")) != NULL)
		fd = ft_atoi(cur + 3);
	else
		fd = 1;
	if (*first <= 0)
		*first = 1;
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

void		print_history(t_history *history, char *elem, uint64_t option)
{
	t_entry	*entry;
	int		first;
	int		last;
	int		fd;
	int		i;

	i = 1;
	entry = entry_roll_back(history->entry);
	fd = get_elem(history, elem, &first, &last);
	while (entry != NULL)
	{
		if (i > last)
			break ;
		else if (i >= first && entry->cmd != NULL)
		{
			if (option & PRINT_ID)
				ft_printf("%-7d%s\n", i, entry->cmd);
			else
				ft_printf("       %s\n", entry->cmd);
		}
		entry = entry->next;
		i++;
	}
}
