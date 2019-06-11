#include "sh21.h"

/*
** remove current node
*/

int		circle_list_pop(t_circle_list **cur)
{
	t_circle_list *current;
	t_circle_list *prev;
	t_circle_list *next;

	if (*cur == NULL)
		return (LIST_EMPTY);
	current = *cur;
	next = current->next;
	prev = current->prev;
	if (next == current && prev == current)
	{
		ft_strdel(&current->name);
		free(current);
		*cur = NULL;
		return (LIST_EMPTY);
	}
	ft_strdel(&current->name);
	free(current);
	current = next;
	current->prev = prev;
	prev->next = current;
	*cur = current;
	return (LIST_OK);
}

/*
** free circle list
*/

void	free_circle_list(t_circle_list *list, t_circle_list *head)
{
	if (list != head)
	{
		free_circle_list(list->next, head);
		ft_strdel(&list->name);
		free(list);
	}
	if (list)
	{
		ft_strdel(&list->name);
		free(list);
	}
}

/*
** set mask: add to mask by ascii number
** ex: 'A' = 65 so 65e bit is activated
*/

static __int128_t set_list_mask(char *s)
{
	__int128_t	mask;

	mask = 0;
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s <= 127)
			mask |= (1 << *s);
		s++;
	}
	return (mask);
}

/*
** create new node
*/

t_circle_list	*circle_list_new(char *name)
{
	t_circle_list	*list;

	if (!(list = (t_circle_list *)malloc(sizeof(t_circle_list))))
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	list->name = name == NULL? NULL : ft_strdup(name);
	list->mask = set_list_mask(name);
	return (list);
}

/*
** add new node
*/

void	circle_list_addback(t_circle_list **alst, t_circle_list *new)
{
	t_circle_list	*cur;

	if (!new)
		return ;
	cur = *alst;
	if (cur != NULL)
	{
		while (cur->next != *alst)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	else
		*alst = new;
	(*alst)->prev = new;
	new->next = *alst;
}
