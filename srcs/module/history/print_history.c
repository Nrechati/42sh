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

static void		print_output(char *cmd, int fd, int line, uint64_t option)
{
	if (option & PRINT_ID)
		ft_dprintf(fd, "%d\t%s\n", line, cmd);
	else if (option & WITHOUT_SPACE)
		ft_dprintf(fd, "%s\n", cmd);
	else
		ft_dprintf(fd, "\t%s\n", cmd);
}

static void		print_reverse(t_history *history, t_param *param,
					uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = history->nb_of_entries;
	entry = history->entry;
	while (entry != NULL && i >= param->first)
	{
		if (i <= param->last && entry->cmd != NULL)
			print_output(entry->cmd, param->fd, i, option);
		entry = entry->prev;
		i--;
	}
}

static void		print_standard(t_history *history, t_param *param,
					uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = 1;
	entry = entry_roll_back(history->entry);
	while (entry != NULL && i <= param->last)
	{
		if (i >= param->first && entry->cmd != NULL)
			print_output(entry->cmd, param->fd, i, option);
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

static void	get_elem(t_history *history, char *elem, t_param *param)
{
	char	*cur;

	param->fd = 1;
	if (elem != NULL && (cur = ft_strstr(elem, "first:")) != NULL)
	{
		param->first = ft_atoi(cur + 6);
		if (param->first <= 0)
			param->first = history->nb_of_entries + param->first + 1;
		if (param->first > history->nb_of_entries)
			param->first = history->nb_of_entries;
	}
	else
		param->first = history->nb_of_entries - 15;
	if (elem != NULL && (cur = ft_strstr(elem, "last:")) != NULL)
	{
		param->last = ft_atoi(cur + 5);
		if (param->last <= 0)
			param->last = -(param->last);
		if (param->last > history->nb_of_entries)
			param->last = history->nb_of_entries;
	}
	else
		param->last = history->nb_of_entries;
	if (elem != NULL && (cur = ft_strstr(elem, "fd:")) != NULL)
		param->fd = ft_atoi(cur + 3);
}


void		print_history(t_history *history, char *elem, uint64_t option)
{
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	get_elem(history, elem, &param);
	if (param.last < param.first)
	{
		option |= REVERSE;
		int_swap(&param.first, &param.last);
	}
	if (option & REVERSE)
		print_reverse(history, &param, option);
	else
		print_standard(history, &param, option);
}