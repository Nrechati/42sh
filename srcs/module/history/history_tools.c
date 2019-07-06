/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:26:32 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 19:26:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
