#include "sh21.h"

static char	*get_entry_by_id(t_history *history, int id, uint64_t option)
{
	t_entry		*entry;
	int			real_id;

	if (id == -1)
		id = history->nb_of_entries - 1;
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
			history->head_ptr = entry;
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

static char	*get_next_or_prev_entry(t_history *history, uint64_t option)
{
	if (history->first_search == TRUE)
	{
		if (option & NEXT)
			return (NULL);
		history->first_search = FALSE;
	}
	else if (option & NEXT)
	{
		if (history->head_ptr->next != NULL)
			history->head_ptr = history->head_ptr->next;
	}
	else if (option & PREV)
	{
		if (history->head_ptr->prev != NULL)
			history->head_ptr = history->head_ptr->prev;
	}
	return (history->head_ptr->cmd);
}

char		*get_entry(t_history *history, char *search, uint64_t option)
{
	if (history->head_ptr == NULL)
		return (NULL);
	else if (option & BY_ID)
	{
		return (get_entry_by_id(history, search == NULL ?
					history->nb_of_entries : ft_atoi(search), option));
	}
	else if (option & BY_NAME)
	{
		if (search == NULL || *search == '\0')
			return (NULL);
		if (option & NEXT)
			return (get_entry_by_name_next(history, search));
		return (get_entry_by_name_prev(history, search));
	}
	else if ((option & NEXT) || (option & PREV))
		return (get_next_or_prev_entry(history, option));
	return (NULL);
}