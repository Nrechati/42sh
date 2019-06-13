#include "sh21.h"

void		add_new_entry(t_history *history, char *new)
{
	if (new == NULL || *new == '\0')
		return ;
	add_entry(&history->entry, create_entry(new));
	history->head_ptr = history->entry;
	history->nb_of_entries--;
}

void		delete_entry(t_history *history, int id)
{
	t_entry		*entry;
	int			rel_id;

	if (id <= 0 || id > history->nb_of_entries)
		ft_dprintf(2, "42sh: No history entry with ID %d\n", id);
	rel_id = history->nb_of_entries - id;
	entry = history->entry;
	while (entry != NULL)
	{
		if (rel_id == 0)
		{
			pop_entry(&entry);
			history->head_ptr = history->entry;
			history->nb_of_entries--;
			return ;
		}
		entry = entry->prev;
		rel_id--;
	}
}

char		*history(t_registry *shell, char *name, uint64_t option)
{
	static t_history	history;

	(void)shell;
	if (option & INIT_HISTORY)
		ft_bzero(&history, sizeof(history));
	else if (option & RESET_HEAD)
		history.head_ptr = history.entry;
	else if (option & ADD_ENTRY)
		add_new_entry(&history, name);
	else if (option & POP_ENTRY)
	{
		if (name != NULL && *name != '\0')
			delete_entry(&history, ft_atoi(name));
	}
	else if (option & GET_ENTRY)
		return (get_entry(&history, name, option));
//	else if (option & WRITE_HISTFILE)
//	else if (option & FREE_HISTORY)
	return (NULL);
}
