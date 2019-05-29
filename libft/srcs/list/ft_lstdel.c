/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:56:27 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static t_list	*eraser(t_list *current, void (*del)(void *))
{
	if (current)
	{
		eraser(current->next, del);
		ft_lstdelone(&current, del);
	}
	return (NULL);
}

void			*ft_lstdel(t_list **alst, void (*del)(void *))
{
	if (!alst || !*alst)
		return (NULL);
	*alst = eraser(*alst, del);
	return (NULL);
}
