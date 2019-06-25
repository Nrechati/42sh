#include "sh21.h"

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

void		int_swap(int *nb1, int *nb2)
{
	int		tmp;

	tmp = *nb1;
	*nb1 = *nb2;
	*nb2 = tmp;
}
