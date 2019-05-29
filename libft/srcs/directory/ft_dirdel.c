/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 07:25:43 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dir_del(void *file)
{
	t_status	*tmp;

	tmp = (t_status *)file;
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->name)
		ft_strdel(&tmp->name);
}

void		ft_dirdel(t_list **dirlist)
{
	ft_lstdel(dirlist, dir_del);
}
