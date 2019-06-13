#include "sh21.h"

static char	*get_entry_by_id(t_history *history, int id, uint64_t option)
{
	t_entry		*entry;
	int			real_id;

	real_id = option & REL ? id : history->nb_of_entries - id;
	entry = history->entry;
	while (entry != NULL)
	{
		if (real_id == 0)
			return (entry->cmd);
		entry = entry->prev;
		real_id--;
	}
	ft_dprintf(2, "42sh: No history entry with %s ID %d\n",
			option & REL ? "relative" : "absolute", id);
	return (NULL);
}

static char	*get_entry_by_name_prev(t_history *history, char *name)
{
	t_entry		*entry;

	entry = history->head_ptr;
	while (entry != NULL)
	{
		if (ft_strstr(entry->cmd, name) != NULL)
		{
			history->head_ptr = entry->prev;
			return (entry->cmd);
		}
		entry = entry->prev;
	}
	return (NULL);
}

static char	*get_entry_by_name_next(t_history *history, char *name)
{
	t_entry		*entry;

	entry = history->head_ptr;
	while (entry != NULL)
	{
		if (ft_strstr(entry->cmd, name) != NULL)
		{
			history->head_ptr = entry->next;
			return (entry->cmd);
		}
		entry = entry->next;
	}
	return (NULL);
}

static char	*get_entry_by_name(t_history *history, char *name, uint64_t option)
{

	if (option & NEXT)
		return (get_entry_by_name_next(history, name));
	return (get_entry_by_name_prev(history, name));
}

char		*get_entry(t_history *history, char *search, uint64_t option)
{
	if (history->head_ptr == NULL)
		return (NULL);
	if (option & BY_ID)
		return (get_entry_by_id(history, ft_atoi(search), option));
	else if (option & BY_NAME)
		return (get_entry_by_name(history, search, option));
	else if (option & NEXT)
	{
		if (history->head_ptr->next != NULL)
			history->head_ptr = history->head_ptr->next;
		return (history->head_ptr->cmd);
	}
	else if (option & PREV)
	{
		if (history->head_ptr->prev != NULL)
			history->head_ptr = history->head_ptr->prev;
		return (history->head_ptr->cmd);
	}
	return (NULL);
}
