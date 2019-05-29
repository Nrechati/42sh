/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:06:45 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "ft_malloc.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *))
{
	if (!alst || !alst)
		return ;
	if (del)
		del((*alst)->data);
	if ((*alst)->data)
		ft_memdel(&(*alst)->data);
	ft_free(*alst);
	*alst = NULL;
}
